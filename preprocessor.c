/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:41:54 by namkim            #+#    #+#             */
/*   Updated: 2022/08/08 16:38:33 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_error	preprocessor(char *str)
{
	int		i;
	t_list	*quote;
	t_list	*temp;

	//1. 포함되지 말아야할 문자가 있는지 '\'
	//2. 닫히지 않은 quote가 있는지
	// if (ft_strstr(str, INHIBIT))
	// {
	// 	printf("inhibit\n");
	// 	return (ERROR);
	// }
	i = 0;
	quote = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!quote)
				quote = ft_lstnew(&str[i]);
			else if (quote && (*quote->content != str[i]))
				ft_lstadd_front(&quote, ft_lstnew(&str[i]));
			else
			{
				temp = quote;
				quote = quote->next;
				free(temp);
				temp = NULL;
			}
		}
		i++;
	}
	if (quote)
	{
		free(quote);
		return (ERROR);
	}
	return (SUCCESS);
}
