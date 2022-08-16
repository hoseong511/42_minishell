/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:52:26 by hossong           #+#    #+#             */
/*   Updated: 2022/08/16 20:39:07 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	move_redir(t_list **tmp, t_list *a, t_list *b)
{
	if (*tmp && ((t_cmd *)(*tmp)->content)->type == PIPE)
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

t_list	*relocate_type(t_data *data)
{
	t_type	type;
	t_list	*cmdlist;
	t_list	*reloc;
	t_list	*tmp;

	reloc = NULL;
	tmp = NULL;
	cmdlist = data->tokenlist;
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

static char	**bind_content(t_list *node, int i)
{
	char	**des;
	int		j;
	t_list	*tmp;

	des = (char **)malloc(sizeof(char *) * (i + 1));
	if (!des)
		ft_error("ERROR: malloc error\n");
	j = -1;
	while (++j < i)
	{
		des[j] = ((t_cmd *)node->content)->str;
		tmp = node->next;
		free(node->content);
		free(node);
		node = tmp;
	}
	des[j] = 0;
	return (des);
}

static void	bind_type(t_list **cmdlist, t_list **bind, t_type type)
{
	t_list	*tmp;
	char	**des;
	int		i;

	tmp = NULL;
	i = 0;
	if (type >= R_IN && type <= R_HEREDOC)
	{
		ft_lstadd_back(&tmp, pop(cmdlist));
		ft_lstadd_back(&tmp, pop(cmdlist));
		i = 2;
	}
	else
	{
		while ((*cmdlist) && ((t_cmd *)(*cmdlist)->content)->type == type)
		{
			ft_lstadd_back(&tmp, pop(cmdlist));
			i++;
		}
	}
	des = bind_content(tmp, i);
	add_cmd2(bind, des, type);
}

static void	bind_cmd(t_list **lst, t_list **tmp)
{
	t_list	*new;

	new = ft_lstnew(*tmp);
	*tmp = NULL;
	ft_lstadd_back(lst, new);
}

t_list	*bind(t_data *data)
{
	t_list	*bind;
	t_list	*tmp;
	t_type	type;

	bind = NULL;
	tmp = NULL;
	while (data->cmdlist)
	{
		type = ((t_cmd *)data->cmdlist->content)->type;
		if (type == PIPE)
		{
			bind_cmd(&bind, &tmp);
			free_cmd(data->cmdlist, "t_cmd");
			free(pop(&data->cmdlist));
		}
		else
			bind_type(&data->cmdlist, &tmp, type);
	}
	if (!data->cmdlist)
		bind_cmd(&bind, &tmp);
	return (bind);
}
