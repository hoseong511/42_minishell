/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:19:24 by hossong           #+#    #+#             */
/*   Updated: 2022/08/13 20:52:53 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	is_end(int c)
{
	return ((c >= 9 && c <= 13) || c == 32 || c == '|' || c == '<' || c == '>');
}

void	add_token(t_list **lst, char *str, int start, size_t len)
{
	char	*sub;
	t_list	*new;
	t_cmd	*token;


	token = (t_cmd *)malloc(sizeof(t_cmd));
	if (!token)
		ft_error("ERROR: malloc error\n");
	sub = ft_substr(str, start, len);
	if (!sub)
		ft_error("ERROR: malloc error\n");
	token->str = sub;
	token->type = NONE;
	new = ft_lstnew(token);
	if (!new)
		ft_error("ERROR: malloc error\n");
	ft_lstadd_back(lst, new);
}

int	check_redir(t_list **lst, char *str, int start)
{
	char	*target;

	target = (str + start);
	if (*target == *(target + 1))
	{
		add_token(lst, str, start, 2);
		return (1);
	}
	else
	{
		add_token(lst, str, start, 1);
		return (0);
	}
}

int	get_quote_end_idx(char *str, int i)
{
	int		j;
	char	q;

	q = str[i];
	j = 1;
	while (str[i + j] && str[i + j] != q)
		j++;
	if (!str[i + j])
		ft_error("unclosed quotes\n");
	return (j);
}

t_list	*tokenizer(char *str)
{
	int		start;
	int		i;
	t_list	*lst;

	lst = NULL;
	start = 0;
	i = -1;
	while (str[++i])
	{
		if (is_end(str[i]))
		{
			if (start != i)
				add_token(&lst, str, start, i - start);
			else if (str[i] == '|')
				add_token(&lst, str, start, 1);
			else if (str[i] == '<' || str[i] == '>')
				i += check_redir(&lst, str, start);
			start = i + 1;
		}
		else if ((str[i] == '\'' || str[i] == '\"'))
			i += get_quote_end_idx(str, i);
	}
	if (str[i] == '\0')
		add_token(&lst, str, start, i);
	return (lst);
}
