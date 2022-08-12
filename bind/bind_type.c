/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:52:26 by hossong           #+#    #+#             */
/*   Updated: 2022/08/12 18:14:38 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bind_type.h"

static t_data	*init_data(void)
{
	t_data	*new;

	new = (t_data *)malloc(sizeof(new));
	if (!new)
		ft_error("Malloc error\n");
	ft_memset(new, 0, sizeof(t_data));
	return (new);
}

t_list	*relocation_type(t_list *cmdlist)
{
	t_list	*bindlist;
	t_list	*head;
	t_list	*tmp;
	t_cmd	*target;

	head = cmdlist;
	bindlist = NULL;
	tmp = NULL;
	while (cmdlist)
	{
		target = (t_cmd *)cmdlist->content;
		if (cmdlist != head && target->type >= R_IN && target->type <= R_HEREDOC)
		{
			if (tmp)
				tmp->next = cmdlist->next->next;
			cmdlist->next->next = head;
		}
		tmp = cmdlist;
		cmdlist = cmdlist->next;
	}
	// ft_lstadd_back(&bindlist, ft_lstnew(str));
	return (bindlist);
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	dummy_data(data);
	relocation_type(data->cmdlist);
}
