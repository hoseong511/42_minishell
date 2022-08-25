/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:27:01 by hossong           #+#    #+#             */
/*   Updated: 2022/08/25 13:21:58 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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
		ft_exit(((t_cmd2 *)args->content)->str, data);
}

void	exec_arg(t_data *data, t_list *args)
{
	char	**arg;
	char	*path;

	if (!args)
		exit(0);
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
}

void	execution(t_data *data)
{
	t_list	*cmdlist;
	t_built	is_built;
	t_list	*node;

	cmdlist = data->cmdlist;
	if (!cmdlist)
		return ;
	data->info = init_proc_info(data);
	if (heredoc(data) == -1)
	{
		close_heredoc(data, NULL);
		return ;
	}
	is_built = check_builtin((t_list *)cmdlist->content);
	if (data->cmd_cnt == 1 && is_built)
	{
		node = redirection_left(data, (t_list *)cmdlist->content);
		node = redirection_right(node);
		exec_builtin(node, data);
	}
	else
		exec_process(data, cmdlist);
	data->cmd_cnt = 0;
	ft_dup2(data->fd_stdin, 0);
	ft_dup2(data->fd_stdout, 1);
}
