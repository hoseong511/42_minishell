/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:09:45 by hossong           #+#    #+#             */
/*   Updated: 2021/11/24 17:44:31 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (*lst == NULL)
	{
		lst = NULL;
		return ;
	}
	tmp = (*lst)->next;
	ft_lstdelone(*lst, del);
	*lst = tmp;
	ft_lstclear(lst, del);
}
