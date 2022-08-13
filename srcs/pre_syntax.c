/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:52:14 by hossong           #+#    #+#             */
/*   Updated: 2022/08/13 15:00:55 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static char	*ft_strstr(char *str, char *to_find)
{
	if (!(*to_find))
		return (str);
	while (*str)
	{
		if (ft_strchr(to_find, *str) != 0)
			return (str);
		str++;
	}
	return (0);
}

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
			else if (quote && (*(char *)(quote->content)) != str[i]) // void* conversion
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