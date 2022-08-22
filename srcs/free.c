/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:45:35 by namkim            #+#    #+#             */
/*   Updated: 2022/08/22 18:37:39 by hossong          ###   ########.fr       */
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

// static void	free_argnode(void *argnode)
// {
// 	char	**strs;
// 	t_list	*node;

// 	node = (t_list *)argnode;
// 	strs = ((t_cmd2 *)node->content)->str;
// 	while (*strs)
// 	{
// 		free(*strs);
// 		*strs = NULL;
// 		strs++;
// 	}
// 	free(((t_cmd2 *)node->content)->str);
// 	free(node->content);
// 	free(argnode);
// }

// static void	free_arglist(void *content)
// {
// 	t_list	*node;

// 	node = (t_list *)content;
// 	ft_lstclear(&node, free_argnode);
// }

void	free_cmdlist(t_list *cmdlist)
{
	t_list	*tmp;
	t_list	*arglist;
	char	**strs;

	while (cmdlist)
	{
		arglist = (t_list *)cmdlist->content;
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
		tmp = cmdlist->next;
		free(cmdlist->content);
		free(cmdlist);
		cmdlist = tmp;
	}
	// ft_lstclear(&cmdlist, free_arglist);
}

void	free_process(t_data *data)
{
	if (data->info)
		free(data->info);
	if (data->heredoc)
		free(data->heredoc);
}
