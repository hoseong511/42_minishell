/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:45:35 by namkim            #+#    #+#             */
/*   Updated: 2022/08/24 20:09:51 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	free_envlist(t_data *data)
{
	char	**envlist;
	int		i;

	envlist = data->envlist;
	i = -1;
	if (!envlist)
		return ;
	while (envlist[++i])
		free(envlist[i]);
	free(envlist);
	data->envlist_cnt = 0;
	data->envlist_size = 0;
}

void	free_arglist(t_list *arglist)
{
	t_list	*tmp;
	char	**strs;

	while (arglist)
	{
		strs = ((t_cmd2 *)arglist->content)->str;
		while (*strs)
		{
			free(*strs);
			strs++;
		}
		free(((t_cmd2 *)arglist->content)->str);
		tmp = arglist->next;
		free(arglist->content);
		free(arglist);
		arglist = tmp;
	}
}

void	free_cmdlist(t_list *cmdlist)
{
	t_list	*tmp;

	while (cmdlist)
	{
		free_arglist((t_list *)cmdlist->content);
		tmp = cmdlist->next;
		free(cmdlist);
		cmdlist = tmp;
	}
}

void	free_process(t_data *data)
{
	if (data->info)
	{
		if (data->info->pid)
			free(data->info->pid);
		free(data->info);
	}
	if (data->heredoc)
		free(data->heredoc);
}

void	free_tokenlist(t_list *tokenlist)
{
	t_list	*node;
	t_list	*temp;

	node = tokenlist;
	while (node)
	{
		temp = node->next;
		free(((t_cmd *)node->content)->str);
		free(node->content);
		free(node);
		node = temp;
	}
}
