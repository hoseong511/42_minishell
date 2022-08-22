/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:27:01 by hossong           #+#    #+#             */
/*   Updated: 2022/08/22 17:15:13 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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

void	close_heredoc(t_data *data, t_list *arglist)
{
	t_cmd2	*arg;
	int		i;

	if (data->heredoc && arglist == NULL)
	{
		i = 0;
		while (data->heredoc[i] == -1)
			i++;
		close(data->heredoc[i]);
		data->heredoc[i] = -1;
	}
	while (arglist)
	{
		arg = (t_cmd2 *)arglist->content;
		if (arg->type == R_HEREDOC)
		{
			i = 0;
			while (data->heredoc[i] == -1)
				i++;
			close(data->heredoc[i]);
			data->heredoc[i] = -1;
		}
		arglist = arglist->next;
	}
}

void	exec_process(t_data *data, t_list *cmdlist)
{
	int		depth;

	data->info = init_proc_info();
	if (heredoc(data) == -1)
	{
		close_heredoc(data, NULL);
		return ;
	}
	depth = 0;
	while (cmdlist && depth < data->cmd_cnt)
	{
		if (data->cmd_cnt != 1)
			init_pipe(data, depth, data->cmd_cnt);
		data->info->pid = fork();
		if (data->info->pid > 0)
		{
			signal(SIGINT, signal_handler_c);
			parent_process(data, depth);
		}
		else if (data->info->pid == 0)
			child_process(data, (t_list *)cmdlist->content, depth);
		else
			ft_perror("fork error", errno);
		close_heredoc(data, (t_list *)cmdlist->content);
		cmdlist = cmdlist->next;
		data->redir = 0;
		depth++;
	}
}

int	count_heredoc(t_list *cmdlist)
{
	t_list	*arglist;
	t_cmd2	*arg;
	int		cnt;

	cnt = 0;
	while (cmdlist)
	{
		arglist = (t_list *)cmdlist->content;
		while (arglist)
		{
			arg = (t_cmd2 *)arglist->content;
			if (arg->type == R_HEREDOC)
				cnt++;
			arglist = arglist->next;
		}
		cmdlist = cmdlist->next;
	}
	if (!cnt)
		return (0);
	return (cnt);
}

int	set_heredoc(t_data *data, t_list *cmdlist)
{
	t_list	*arglist;
	t_cmd2	*arg;
	int		i;

	i = 0;
	while (cmdlist)
	{
		arglist = (t_list *)cmdlist->content;
		while (arglist)
		{
			arg = (t_cmd2 *)arglist->content;
			if (arg->type == R_HEREDOC)
			{
				redirection_heredoc(data, arg->str[1], i);
				if (g_status == 1)
					return (-1);
				i++;
			}
			arglist = arglist->next;
		}
		cmdlist = cmdlist->next;
	}
	return (0);
}

int	heredoc(t_data *data)
{
	int	cnt;

	cnt = count_heredoc(data->cmdlist);
	if (cnt == 0)
		return (0);
	data->heredoc = (int *)malloc(sizeof(int) * (cnt + 1));
	if (!data->heredoc)
		ft_perror("Malloc", errno);
	data->heredoc[cnt] = -2;
	if (set_heredoc(data, data->cmdlist) == -1)
		return (-1);
	return (0);
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
