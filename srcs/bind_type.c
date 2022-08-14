/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:52:26 by hossong           #+#    #+#             */
/*   Updated: 2022/08/14 14:06:44 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	add_cmd2(t_list **lst, char **str, t_type type)
{
	t_cmd2	*cmd2;
	t_list	*new;

	cmd2 = (t_cmd2 *)malloc(sizeof(t_cmd2));
	if (!cmd2)
		ft_error("ERROR: malloc error\n");
	cmd2->str = str;
	cmd2->type = type;
	new = ft_lstnew(cmd2);
	if (!new)
		ft_error("ERROR: malloc error\n");
	ft_lstadd_back(lst, new);
}

void	move_redir(t_list **tmp, t_list *a, t_list *b)
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
	cmdlist = data->cmdlist;
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

char	**bind_content(t_list *node, int i)
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
		free(node);
		node = tmp;
	}
	des[j] = 0;
	return (des);
}

t_list	*bind_type(t_data *data)
{
	t_list	*bind;
	t_list	*tmp;
	t_type	type;
	char	**des;
	int		i;

	bind = NULL;
	while (data->cmdlist)
	{
		i = 0;
		tmp = NULL;
		type = ((t_cmd *)data->cmdlist->content)->type;
		if (type == PIPE)
			free(pop(&data->cmdlist));
		while (data->cmdlist && ((t_cmd *)data->cmdlist->content)->type == type)
		{
			ft_lstadd_back(&tmp, pop(&data->cmdlist));
			i++;
		}
		des = bind_content(tmp, i);
		add_cmd2(&bind, des, type);
	}
	return (bind);
}
