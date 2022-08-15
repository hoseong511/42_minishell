/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 01:17:11 by hossong           #+#    #+#             */
/*   Updated: 2022/08/13 16:24:06 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	insert(t_list *a, t_list *b)
{
	b->next = a->next;
	a->next = b;
}

void	push(t_list **list, t_list *node)
{
	ft_lstadd_front(list, node);
}

t_list	*pop(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	if (tmp->next != NULL)
	{
		(*list) = tmp->next;
		tmp->next = NULL;
	}
	else
		(*list) = NULL;
	return (tmp);
}

void	clear(char **lst, int i)
{
	while (i--)
		free(lst[i]);
	free(lst);
}
