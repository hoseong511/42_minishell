/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:52:26 by hossong           #+#    #+#             */
/*   Updated: 2022/08/12 21:44:03 by hossong          ###   ########.fr       */
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

t_list	*cut_list(t_list **list, t_list *a, int len)
{
	t_list	*prev;
	t_list	*current;

	while (*list != a)
	{
		prev = *list;
		*list = (*list)->next;
	}
	current = a;
	while (current && --len)
		current = current->next;
	if (current)
	{
		prev->next = current->next;
		current->next = NULL;
	}
	else
		prev->next = NULL;
	return (a);
}

void	inset_list(t_list *a, t_list *b, int len)
{
	t_list	*tmp;

	tmp = cut_list(&a, b, len);
	while (b && --len)
		b = b->next;
	b->next = a->next;
	a->next = tmp;
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

void	relocation_type(t_list *cmdlist)
{
	t_list	*head;
	t_list	*tmp;
	t_list	*tmp_pipe;
	t_type	type;

	head = cmdlist;
	tmp_pipe = NULL;
	while (cmdlist)
	{
		type = ((t_cmd *)cmdlist->content)->type;
		if (cmdlist != head && type >= R_IN && type <= R_HEREDOC)
		{
			if (tmp_pipe)
				inset_list(tmp_pipe, cmdlist, 2);
			else
			{
				tmp = cut_list(&head, cmdlist, 2);
				tmp->next->next = head;
			}
			cmdlist = cmdlist->next->next;
			continue ;
		}
		if (type == PIPE)
			tmp_pipe = cmdlist;
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
