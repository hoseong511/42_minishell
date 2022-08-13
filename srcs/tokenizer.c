/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:19:24 by hossong           #+#    #+#             */
/*   Updated: 2022/08/14 02:28:07 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	is_end(int c)
{

	return ((c >= 9 && c <= 13) || c == 32 \
			|| c == '|' || c == '<' \
			|| c == '>' || c == '\0');
}

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

int	add_quote_token(t_list **lst, char *str)
{
	int		j;
	char	q;

	q = *str;
	j = 1;
	while (str[j] && str[j] != q)
		j++;
	if (str[j] == q)
		add_token(lst, str, j);
	else
		ft_error("unclosed quotes\n");
	return (j);
}

int	add_end_token(t_list **lst, char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (!is_end(str[i]))
		i++;
	if (str[i] == '|')
		add_token(lst, str + i, 1);
	else if (str[i] == '<' || str[i] == '>')
	{
		if (str[i + 1] && str[i] == str[i + 1])
		{
			add_token(lst, str, 2);
			ret = 1;
		}
		else
			add_token(lst, str, 1);
	}
	else if (str[i] == '\0')
	{
		add_token(lst, str, i);
		ret = i;
	}
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
			i += add_end_token(&lst, str + i);
		else if (str[i] == '<' || str[i] == '>')
			i += add_end_token(&lst, str + i);
		else if ((str[i] == '\'' || str[i] == '\"'))
			i += add_quote_token(&lst, str + i);
		else
			i += add_end_token(&lst, str + i);
	}
	return (lst);
}
