/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:52:26 by hossong           #+#    #+#             */
/*   Updated: 2022/08/12 23:07:10 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bind_type.h"
#include <string.h>

static t_data	*init_data(void)
{
	t_data	*new;

	new = (t_data *)malloc(sizeof(new));
	if (!new)
		ft_error("Malloc error\n");
	memset(new, 0, sizeof(t_data));
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
	// t_list	*tmp;
	// t_list	*tmp_pipe;
	t_type	type;
	t_list	*reloc;

	// tmp_pipe = NULL;
	reloc = NULL;
	while (cmdlist)
	{
		type = ((t_cmd *)cmdlist->content)->type;
		if (type >= R_IN && type <= R_HEREDOC)
			push(&reloc, pop(&cmdlist));
		else
			ft_lstadd_back(&reloc, pop(&cmdlist));
	}
	while (reloc)
	{
		printf("%s\n", ((t_cmd *)reloc->content)->str);
		reloc = reloc->next;
	}
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	dummy_data(data);
	while (data->cmdlist)
	{
		printf("%s\n", ((t_cmd *)data->cmdlist->content)->str);
		data->cmdlist = data->cmdlist->next;
	}
	// relocation_type(data->cmdlist);
}
