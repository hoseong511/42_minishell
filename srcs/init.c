/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:46:57 by namkim            #+#    #+#             */
/*   Updated: 2022/08/19 20:51:43 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	get_envlist_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

t_data	*init_data(char **envp)
{
	t_data	*res;

	res = malloc(sizeof(t_data));
	if (!res)
		ft_error("Malloc Error While Initialize\n");
	res->envlist = get_env(envp);
	res->envlist_cnt = get_envlist_size(res->envlist);
	res->envlist_size = get_envlist_size(res->envlist);
	res->tokenlist = NULL;
	res->cmdlist = NULL;
	res->cmd_cnt = 0;
	res->status = TRUE;
	return (res);
}

void	load_data(t_data *data, char *str)
{
	data->status = check_quote(str);
	if (data->status == FALSE)
		return ;
	data->tokenlist = tokenizer(str);
	print_t_cmds(data->tokenlist);
	if (!data->tokenlist)
		return ;
	data->tokenlist = lexer(data);
	print_t_cmds(data->tokenlist);
	printf("=========================\n");
	data->cmdlist = relocate(data->tokenlist);
	data->cmdlist = bind(data->cmdlist);
	print_t_cmds2(data->cmdlist);
	// t_cmd2	*cmd2cont;
	// cmd2cont = data->cmdlist->content;
	// printf("path : %s\n", path[0]);
	// printf("path : %s\n", path[1]);
	// printf("path : %s\n", path[2]);
	// printf("path : %s\n", path[3]);
	// printf("path : %s\n", path[4]);
//	printf("cmdnode->str: %s\n", cmd2cont->str[0]);
	// get_exe_file(data->envlist, cmd2cont->str[0]);
}
