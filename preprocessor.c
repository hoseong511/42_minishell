/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:41:54 by namkim            #+#    #+#             */
/*   Updated: 2022/08/08 18:10:57 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//1. 포함되지 말아야할 문자가 있는지 '\'
//2. 닫히지 않은 quote가 있는지
static void	pop_quote(t_list **quote)
{
	t_list	*temp;

	temp = *quote;
	*quote = (*quote)->next;
	free(temp);
}

t_error	check_quote(char *str)
{
	int		i;
	t_list	*quote;

	i = -1;
	quote = NULL;
	if (ft_strstr(str, INHIBIT))
		return (ERROR);
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!quote)
				quote = ft_lstnew(&str[i]);
			else if (quote && (*(char *)(quote->content)) != str[i])
				ft_lstadd_front(&quote, ft_lstnew(&str[i]));
			else
				pop_quote(&quote);
		}
	}
	if (quote)
	{
		free(quote);
		return (ERROR);
	}
	return (SUCCESS);
}

void	replace_env(char **str, char **envp)
{
	int		i;
	char	*var;
	char	*prev;
	char	*next;
	int 	d;

	i = -1;
	(void) envp;
	while ((*str)[++i])
	{
		if ((*str)[i] == '$')
		{
			i++;
			if ((*str)[i] == '\'')
			{
				d = ft_strchr(*str + i + 1, '\'') - (*str + i);
				i += d;
				printf("str[i]: %c", (*str)[i]);
			}
			else
			{
				d = ft_strchr(*str + i, ' ') - (*str + i);
				prev = ft_strndup(*str, i - 1);
				var = ft_strndup(*str + i, d);
				next = ft_strdup(*str + i + d + 1);
				printf("prev: %s\n", prev);
				printf("var: %s\n", var);
				printf("next: %s\n", next);
			}
		}
	}
}
