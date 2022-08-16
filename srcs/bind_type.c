/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:52:26 by hossong           #+#    #+#             */
/*   Updated: 2022/08/17 00:35:49 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_list	*relocate(t_list *tokenlist)
{
	t_type	type;
	t_list	*des;
	t_list	*src;
	t_list	*tmp;

	des = NULL;
	tmp = NULL;
	src = NULL;
	while (tokenlist)
	{
		type = ((t_cmd *)tokenlist->content)->type;
		if (type >= R_IN && type <= R_HEREDOC)
			append_ab(&src, pop(&tokenlist), pop(&tokenlist));
		else if (type == PIPE)
		{
			insert_src(&des, &src, &tmp);
			tmp = pop(&tokenlist);
			ft_lstadd_back(&des, tmp);
		}
		else
			ft_lstadd_back(&des, pop(&tokenlist));
		if (!tokenlist)
			insert_src(&des, &src, &tmp);
	}
	return (des);
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
