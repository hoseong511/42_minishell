/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:27:01 by hossong           #+#    #+#             */
/*   Updated: 2022/08/19 20:25:34 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	exec_arg(t_data *data, t_list *args)
{
	char	**arg;
	char	*path;

	arg = ((t_cmd2 *)args->content)->str;
	if (check_builtin(args))
		exec_builtin(args, data);
	path = get_exe_file(data->envlist, arg[0]);
	execve(path, arg, data->envlist);
	exit(1);
}

void	exec_process(t_data *data, t_list *cmdlist)
{
	int	depth;

	data->info = init_proc_info();
	depth = 0;
	while (cmdlist && depth < data->cmd_cnt)
	{
		if (data->cmd_cnt != 1)
			init_pipe(data, depth, data->cmd_cnt);
		//redirection_left((t_list *)cmdlist->content);
		data->info->pid = fork();
		if (data->info->pid > 0)
			parent_process(data, depth);
		else if (data->info->pid == 0)
			child_process(data, (t_list *)cmdlist->content, depth);
		else
			ft_perror("fork error", errno);
		cmdlist = cmdlist->next;
		depth++;
	}
}

void	execution(t_data *data)
{
	t_list	*cmdlist;
	t_built	is_built;

	cmdlist = data->cmdlist;
	if (!cmdlist)
		return ;
	is_built = check_builtin((t_list *)cmdlist->content);
	if (data->cmd_cnt == 1 && is_built)
		exec_builtin((t_list *)cmdlist->content, data);
	else
		exec_process(data, cmdlist);
	data->cmd_cnt = 0;
}
