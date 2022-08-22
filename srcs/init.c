/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:46:57 by namkim            #+#    #+#             */
/*   Updated: 2022/08/22 21:54:30 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_data	*init_data(char **envp)
{
	t_data	*res;

	res = malloc(sizeof(t_data));
	if (!res)
		ft_error("Malloc Error While Initialize\n");
	res->envlist = get_env(envp, res);
	res->envlist_cnt = res->envlist_size;
	res->tokenlist = NULL;
	res->cmdlist = NULL;
	res->cmd_cnt = 0;
	res->status = TRUE;
	res->heredoc = 0;
	res->fd_stdin = dup(0);
	res->fd_stdout = dup(1);
	g_status = 0;
	return (res);
}

void	re_initialize(t_data *data)
{
	free_process(data);
	free_cmdlist(data->cmdlist);
	data->cmdlist = NULL;
	data->tokenlist = NULL;
	data->cmd_cnt = 0;
	data->status = TRUE;
	data->info = NULL;
	data->heredoc = 0;
}

void	load_data(t_data *data, char *str)
{
	data->tokenlist = tokenizer(str);
	if (!data->tokenlist)
		return ;
	data->tokenlist = lexer(data);
	data->cmdlist = relocate(&data->tokenlist);
	data->cmdlist = bind(data->cmdlist);
}
