/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bind.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:52:26 by hossong           #+#    #+#             */
/*   Updated: 2022/08/22 21:02:02 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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

t_list	*bind(t_list *cmdlist)
{
	t_list	*bind;
	t_list	*tmp;
	t_type	type;

	bind = NULL;
	tmp = NULL;
	while (cmdlist)
	{
		type = ((t_cmd *)cmdlist->content)->type;
		if (type == PIPE)
		{
			bind_cmd(&bind, &tmp);
			free(((t_cmd *)cmdlist->content)->str);
			free(cmdlist->content);
			free(pop(&cmdlist));
		}
		else
			bind_type(&cmdlist, &tmp, type);
	}
	if (!cmdlist)
		bind_cmd(&bind, &tmp);
	return (bind);
}
