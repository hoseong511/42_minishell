/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:19:24 by hossong           #+#    #+#             */
/*   Updated: 2022/08/15 16:13:10 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	add_token(t_list **lst, char *str, size_t len)
{
	char	*sub;
	t_list	*new;

	sub = ft_strndup(str, len);
	if (!sub)
		ft_error("ERROR: malloc error\n");
	new = ft_lstnew(sub);
	if (!new)
		ft_error("ERROR: malloc error\n");
	ft_lstadd_back(lst, new);
}

int	add_quote_idx(char *str)
{
	int		j;
	char	q;

	q = *str;
	j = 1;
	while (str[j] && str[j] != q)
		j++;
	if (str[j] != q)
		ft_error("unclosed quotes\n");
	return (j);
}

int	add_end_token(t_list **lst, char *str)
{
	int	i;

	i = 0;
	while (!((str[i] >= 9 && str[i] <= 13) || str[i] == 32 \
			|| str[i] == '|' || str[i] == '<' \
			|| str[i] == '>' || str[i] == '\0'))
		i++;
	add_token(lst, str, i);
	return (i - 1);
}

int	add_redir_token(t_list **lst, char *str)
{
	int	ret;

	ret = 0;
	if (*(str + 1) && *str == *(str + 1))
	{
		add_token(lst, str, 2);
		ret = 1;
	}
	else
		add_token(lst, str, 1);
	return (ret);
}

t_list	*tokenizer(char *str)
{
	t_list	*lst;
	int		i;

	lst = NULL;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '|')
			add_token(&lst, str + i, 1);
		else if (str[i] == '<' || str[i] == '>')
			i += add_redir_token(&lst, str + i);
		else if ((str[i] == '\'' || str[i] == '\"'))
			i += add_quote_idx(str + i);
		else if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			;
		else
			i += add_end_token(&lst, str + i);
	}
	return (lst);
}
