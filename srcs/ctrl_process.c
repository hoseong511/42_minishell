/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:32:30 by hossong           #+#    #+#             */
/*   Updated: 2022/08/21 19:48:28 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

extern int	g_status;

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
			ret = B_ECHO;
		else if (ft_strncmp(arg->str[0], "cd", 3) == 0)
			ret = B_CD;
		else if (ft_strncmp(arg->str[0], "pwd", 4) == 0)
			ret = B_PWD;
		else if (ft_strncmp(arg->str[0], "export", 7) == 0)
			ret = B_EXPORT;
		else if (ft_strncmp(arg->str[0], "unset", 6) == 0)
			ret = B_UNSET;
		else if (ft_strncmp(arg->str[0], "env", 4) == 0)
			ret = B_ENV;
		else if (ft_strncmp(arg->str[0], "exit", 5) == 0)
			ret = B_EXIT;
	}
	return (ret);
}

void	exec_builtin(t_list *args, t_data *data)
{
	t_built	builtin;

	builtin = check_builtin(args);
	if (!builtin)
		return ;
	else if (builtin == B_ECHO)
		ft_echo(((t_cmd2 *)args->content)->str);
	else if (builtin == B_CD)
		ft_cd(((t_cmd2 *)args->content)->str, data);
	else if (builtin == B_PWD)
		ft_pwd(((t_cmd2 *)args->content)->str);
	else if (builtin == B_EXPORT)
		ft_export(((t_cmd2 *)args->content)->str, data);
	else if (builtin == B_UNSET)
		ft_unset(((t_cmd2 *)args->content)->str, data);
	else if (builtin == B_ENV)
		ft_env(((t_cmd2 *)args->content)->str, data);
	else if (builtin == B_EXIT)
		ft_exit();
}

void	child_process(t_data *data, t_list *args, int depth)
{
	t_list	*node;

	set_termattr(data->save);
	pipe_io(data, depth, data->cmd_cnt);
	node = redirection_right(args);
	exec_arg(data, node);
}

void	parent_process(t_data *data, int depth)
{
	if (data->cmd_cnt < 2)
		wait(&data->info->status);
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
		while (wait(&data->info->status) != -1)
			;
		if (depth % 2 == 0)
			close(data->info->pipe[1].fd[0]);
		else
			close(data->info->pipe[0].fd[0]);
	}
	g_status = WEXITSTATUS(data->info->status);
}
