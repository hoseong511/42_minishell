/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:52:26 by hossong           #+#    #+#             */
/*   Updated: 2022/08/13 16:26:36 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	move_redir(t_list **tmp, t_list *a, t_list *b)
{
	if (((t_cmd *)(*tmp)->content)->type == PIPE)
	{
		insert(*tmp, b);
		insert(*tmp, a);
	}
	else
	{
		push(tmp, b);
		push(tmp, a);
	}
}

t_list	*relocate_type(t_list *cmdlist)
{
	t_type	type;
	t_list	*reloc;
	t_list	*tmp;

	reloc = NULL;
	tmp = NULL;
	while (cmdlist)
	{
		type = ((t_cmd *)cmdlist->content)->type;
		if (type == PIPE)
				tmp = cmdlist;
		if (type >= R_IN && type <= R_HEREDOC)
		{
			if (tmp && ((t_cmd *)tmp->content)->type == PIPE)
				move_redir(&tmp, pop(&cmdlist), pop(&cmdlist));
			else
				move_redir(&reloc, pop(&cmdlist), pop(&cmdlist));
		}
		else
			ft_lstadd_back(&reloc, pop(&cmdlist));
	}
	return (reloc);
}
