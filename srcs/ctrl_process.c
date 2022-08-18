/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:32:30 by hossong           #+#    #+#             */
/*   Updated: 2022/08/18 13:26:54 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_built	check_builtin(t_list *args)
{
	t_cmd2	*arg;
	int		ret;

	ret = 0;
	while (args && ((t_cmd2 *)args->content)->type != ARGS)
		args = args->next;
	if (args)
	{
		arg = (t_cmd2 *)args->content;
		if (ft_strncmp(arg->str[0], "echo", 5) == 0)
			ret = ECHO;
		else if (ft_strncmp(arg->str[0], "cd", 3) == 0)
			ret = CD;
		else if (ft_strncmp(arg->str[0], "pwd", 4) == 0)
			ret = PWD;
		else if (ft_strncmp(arg->str[0], "export", 7) == 0)
			ret = EXPORT;
		else if (ft_strncmp(arg->str[0], "unset", 6) == 0)
			ret = UNSET;
		else if (ft_strncmp(arg->str[0], "env", 4) == 0)
			ret = ENV;
		else if (ft_strncmp(arg->str[0], "exit", 5) == 0)
			ret = EXIT;
	}
	return (ret);
}

void	exec_builtin(t_list *args)
{
	t_built	no;

	no = check_builtin(args);
	if (!no)
		return ;
	else if (no == ECHO)
		;
	else if (no == CD)
		;
	else if (no == PWD)
		;
	else if (no == EXPORT)
		;
	else if (no == UNSET)
		;
	else if (no == ENV)
		;
	else if (no == EXIT)
		;
}

void	do_child_proc(t_data *data, t_list *c_node, int depth)
{
	(void)data;
	(void)c_node;
	(void)depth;
	redirection();
	excute_cmd();
	sleep(2);
	exit(1);
}

void	do_parent_proc(t_data *data, int depth)
{
	(void)data;
	(void)depth;
	if (data->cmd_cnt > 1)
	{
		if (depth % 2 == 0)
			close(data->info->pipe[0].fd[1]);
		else
		{
			close(data->info->pipe[0].fd[0]);
			close(data->info->pipe[1].fd[1]);
		}
	}
	if (depth == data->cmd_cnt - 1)
	{
		while (wait(&data->info->status) != -1)
			;
		printf("parent, exit_status : %d\n", WEXITSTATUS(data->info->status));
		//close(data->info->pipe[1].fd[0]);
	}
}
