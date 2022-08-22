/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:32:30 by hossong           #+#    #+#             */
/*   Updated: 2022/08/22 21:51:36 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_proc	*init_proc_info(void)
{
	t_proc	*new;

	new = (t_proc *)malloc(sizeof(t_proc));
	if (!new)
		ft_error("ERROR: Malloc Error\n");
	ft_memset(new, 0, sizeof(t_proc));
	return (new);
}

void	child_process(t_data *data, t_list *args, int depth)
{
	t_list	*node;

	set_termattr(data->save);
	pipe_in(data, depth, data->cmd_cnt);
	node = redirection_left(data, args);
	pipe_out(data, depth, data->cmd_cnt);
	node = redirection_right(node);
	exec_arg(data, node);
}

void	parent_process(t_data *data, int depth)
{
	signal(SIGINT, signal_handler_c);
	if (data->cmd_cnt == 1)
		wait(&data->info->status);
	else if (depth == 0)
		close(data->info->pipe[0].fd[1]);
	else if (depth != data->cmd_cnt - 1)
		close_pipe(data, depth);
	else if (depth == data->cmd_cnt - 1)
	{
		while (wait(&data->info->status) != -1)
			;
		if (depth % 2 == 0)
			close(data->info->pipe[1].fd[0]);
		else
			close(data->info->pipe[0].fd[0]);
	}
	if (WIFSIGNALED(data->info->status))
	{
		g_status = 130;
		close_heredoc(data, NULL);
	}
	else
		g_status = WEXITSTATUS(data->info->status);
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
			parent_process(data, depth);
		else if (data->info->pid == 0)
			child_process(data, (t_list *)cmdlist->content, depth);
		else
			ft_perror("fork error", errno);
		close_heredoc(data, (t_list *)cmdlist->content);
		cmdlist = cmdlist->next;
		depth++;
	}
}
