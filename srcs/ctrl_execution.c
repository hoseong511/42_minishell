/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:27:01 by hossong           #+#    #+#             */
/*   Updated: 2022/08/20 16:25:40 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	exec_arg(t_data *data, t_list *args)
{
	char	**arg;
	char	*path;

	arg = ((t_cmd2 *)args->content)->str;
	if (check_builtin(args))
	{
		exec_builtin(args, data);
		exit(0);
	}
	if (ft_strchr(arg[0], '/'))
			path = arg[0];
	else
		path = get_exe_file(data->envlist, arg[0]);
	execve(path, arg, data->envlist);
	ft_perror(arg[0], errno);
	exit(1);
}

void	exec_process(t_data *data, t_list *cmdlist)
{
	t_list	*node;
	int		depth;

	data->info = init_proc_info();
	depth = 0;
	while (cmdlist && depth < data->cmd_cnt)
	{
		if (data->cmd_cnt != 1)
			init_pipe(data, depth, data->cmd_cnt);
		node = redirection_left(data, (t_list *)cmdlist->content);
		data->info->pid = fork();
		if (data->info->pid > 0)
			parent_process(data, depth);
		else if (data->info->pid == 0)
			child_process(data, node, depth);
		else
			ft_perror("fork error", errno);
		cmdlist = cmdlist->next;
		data->redir = 0;
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
	ft_dup2(data->stdin_fd, 0);
	ft_dup2(data->stdout_fd, 1);
}
