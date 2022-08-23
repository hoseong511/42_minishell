/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 21:35:13 by namkim            #+#    #+#             */
/*   Updated: 2022/08/23 08:47:33 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	print_t_cmds(t_list *tokenlist)
{
	t_list	*node;
	int		type;
	char	*str;
	int		idx;

	node = tokenlist;
	if (!node)
		printf("No tokens\n");
	idx = 0;
	while (node)
	{
		type = ((t_cmd *)node->content)->type;
		str = ((t_cmd *)node->content)->str;
		printf("[%d] <%d> %s\n", idx, type, str);
		node = node->next;
		idx++;
	}
}

static void	print_cmdnode(t_list *node)
{
	int		type;
	char	**str;
	t_list	*content;

	content = node->content;
	while (content)
	{
		type = ((t_cmd2 *)content->content)->type;
		str = ((t_cmd2 *)content->content)->str;
		printf("[%d] : ", type);
		while (*str)
		{
			printf("%s ", *str);
			str++;
		}
		content = content->next;
	}
}

void	print_t_cmds2(t_list *cmdlist)
{
	t_list	*node;

	node = cmdlist;
	if (!node)
		printf("No tokens\n");
	while (node)
	{
		print_cmdnode(node);
		printf("\n");
		node = node->next;
	}
}

void	print_data(t_data *data)
{
	printf("g_status : %d\n", g_status);
	//termios
	ft_env(data->envlist, data);
	printf("envlist_size : %d\n", data->envlist_size);
	printf("envlist_cnt : %d\n", data->envlist_cnt);
	printf("tokenlist : %p\n", data->tokenlist);
	printf("cmdlist : %p\n", data->cmdlist);
	printf("status : %d\n", data->status);
	printf("t_proc info : %p\n", data->info);
	printf("redir : %d\n", data->redir);
	printf("heredoc : %p\n", data->heredoc);
}
