/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:32:30 by hossong           #+#    #+#             */
/*   Updated: 2022/08/19 12:03:48 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_proc	*init_proc_info(void)
{
	t_proc	*new;

	new = (t_proc *)malloc(sizeof(t_proc));
	if (!new)
		ft_error("ERROR: Malloc Error\n");
	ft_memset(new, 0, sizeof(t_proc));
	return (new);
}

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
	t_built	builtin;

	builtin = check_builtin(args);
	if (!builtin)
		return ;
	else if (builtin == ECHO)
		printf("ECHO\n");
	else if (builtin == CD)
		printf("CD\n");
	else if (builtin == PWD)
		printf("PWD\n");
	else if (builtin == EXPORT)
		printf("EXPORT\n");
	else if (builtin == UNSET)
		printf("UNSET\n");
	else if (builtin == ENV)
		printf("ENV\n");
	else if (builtin == EXIT)
		printf("EXIT\n");
	exit(0);
}

void	child_process(t_data *data, t_list *args, int depth)
{
	t_list	*node;

	(void)depth;
	pipe_io(data, depth, data->cmd_cnt);
	node = redirection(args);
	exec_arg(data, node);
}

void	parent_process(t_data *data, int depth)
{
	wait(&data->info->status);
	if (data->cmd_cnt < 2)
		;
	else if (depth == 0)
		close(data->info->pipe[0].fd[1]);
	else if (depth != data->cmd_cnt - 1)
	{
		if (depth % 2 == 0)
		{
			close(data->info->pipe[1].fd[0]);
			close(data->info->pipe[0].fd[1]);
		}
		else
		{
			close(data->info->pipe[0].fd[0]);
			close(data->info->pipe[1].fd[1]);
		}
	}
	else
	{
		if (depth % 2 == 0)
			close(data->info->pipe[1].fd[0]);
		else
			close(data->info->pipe[0].fd[0]);
	}
	data->exit_status = WEXITSTATUS(data->info->status);
}
