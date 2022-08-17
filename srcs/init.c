/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:46:57 by namkim            #+#    #+#             */
/*   Updated: 2022/08/17 20:25:39 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_data	*init_data(char **envp)
{
	t_data	*res;

	res = malloc(sizeof(t_data));
	if (!res)
		ft_error("Malloc Error While Initialize\n");
	res->envlist = get_env(envp);
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
	if (!data->tokenlist)
		return ;
	data->tokenlist = lexer(data);
	printf("=========================\n");
	data->cmdlist = relocate(data->tokenlist);
	data->cmdlist = bind(data->cmdlist);
	print_t_cmds2(data->cmdlist);
	t_cmd2	*cmd2cont;
	char	**path;
	cmd2cont = data->cmdlist->content;
	path = get_path(data);
	// printf("path : %s\n", path[0]);
	// printf("path : %s\n", path[1]);
	// printf("path : %s\n", path[2]);
	// printf("path : %s\n", path[3]);
	// printf("path : %s\n", path[4]);
//	printf("cmdnode->str: %s\n", cmd2cont->str[0]);
	get_exe_file(path, cmd2cont->str[0], data);
}
