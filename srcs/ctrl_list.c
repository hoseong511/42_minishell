/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 01:17:11 by hossong           #+#    #+#             */
/*   Updated: 2022/08/17 00:18:25 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	insert(t_list **a, t_list *b)
{
	if (*a)
	{
		ft_lstlast(b)->next = (*a)->next;
		(*a)->next = b;
	}
	else
		*a = b;
}

t_list	*pop(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	if (tmp && tmp->next != NULL)
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

void	append_ab(t_list **lst, t_list *a, t_list *b)
{
	ft_lstadd_back(lst, a);
	ft_lstadd_back(lst, b);
}

void	insert_src(t_list **des, t_list **src, t_list **tmp)
{
	if (!(*tmp))
	{
		ft_lstadd_front(des, ft_lstlast(*src));
		*des = *src;
	}
	else
		insert(tmp, *src);
	*src = NULL;
}