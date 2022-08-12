/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:52:26 by hossong           #+#    #+#             */
/*   Updated: 2022/08/13 01:33:43 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bind_type.h"
#include <string.h>

static t_data	*init_data(void)
{
	t_data	*new;

	new = (t_data *)malloc(sizeof(t_data));
	if (!new)
		ft_error("Malloc error\n");
	ft_memset(new, 0, sizeof(t_data));
	return (new);
}

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

int	main(void)
{
	t_data	*data;

	data = init_data();
	dummy_data(data);
	data->cmdlist = relocate_type(data->cmdlist);
	t_list	*reloc = data->cmdlist;
	while (reloc)
	{
		printf("%s\n", ((t_cmd *)(reloc->content))->str);
		reloc = reloc->next;
	}
}
