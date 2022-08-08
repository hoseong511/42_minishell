/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:55:05 by hossong           #+#    #+#             */
/*   Updated: 2021/11/28 13:38:48 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dst;
	t_list	*current;

	if (lst == NULL || f == NULL)
		return (NULL);
	dst = ft_lstnew(f(lst->content));
	if (dst == NULL)
		return (NULL);
	current = dst;
	lst = lst->next;
	while (lst != NULL)
	{
		current->next = ft_lstnew(f(lst->content));
		if (current->next == NULL)
		{
			ft_lstclear(&dst, del);
			return (NULL);
		}
		current = current->next;
		lst = lst->next;
	}
	return (dst);
}
