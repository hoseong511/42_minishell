/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:52:26 by hossong           #+#    #+#             */
/*   Updated: 2022/08/12 19:59:51 by hossong          ###   ########.fr       */
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

void	append_list(t_list *a, t_list *b)
{
	t_list	*last_a;

	last_a = ft_lstlast(a);
	last_a->next = b;
}

void	relocation_type(t_list *cmdlist)
{
	t_list	*head;
	t_list	*tmp;
	t_type	type;

	head = cmdlist;
	tmp = NULL;
	while (cmdlist)
	{
		type = ((t_cmd *)cmdlist->content)->type;
		if (cmdlist != head && type >= R_IN && type <= R_HEREDOC)
		{
			tmp->next = cmdlist->next->next;
			cmdlist->next->next = NULL;
			append_list(cmdlist, head);
			cmdlist = tmp->next;
			tmp = cmdlist;
			continue ;
		}
		if (type == PIPE)
		{

		}
		tmp = cmdlist;
		cmdlist = cmdlist->next;
	}
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	dummy_data(data);
	relocation_type(data->cmdlist);
}
