/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:32:30 by hossong           #+#    #+#             */
/*   Updated: 2022/08/23 16:09:45 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_proc	*init_proc_info(t_data *data)
{
	t_proc	*new;

	new = (t_proc *)malloc(sizeof(t_proc));
	if (!new)
		ft_perror("Malloc", errno);
	ft_memset(new, 0, sizeof(t_proc));
	new->pid = (pid_t *)malloc(sizeof(pid_t) * data->cmd_cnt);
	if (!new->pid)
		ft_perror("Malloc", errno);
	return (new);
}

static void	if_signaled(t_data *data)
{
	if (WIFSIGNALED(data->info->status))
	{
		g_status = 130;
		close_heredoc(data, NULL);
	}
	else
		g_status = WEXITSTATUS(data->info->status);
}

void	child_process(t_data *data, t_list *args, int depth)
{
	t_list	*node;

	set_termattr(data->save);
	signal(SIGINT, signal_handler_e);
	pipe_in(data, depth, data->cmd_cnt);
	node = redirection_left(data, args);
	pipe_out(data, depth, data->cmd_cnt);
	node = redirection_right(node);
	exec_arg(data, node);
}

void	parent_process(t_data *data, int depth)
{
	int	i;

	signal(SIGINT, signal_handler_c);
	if (data->cmd_cnt == 1)
		wait(&data->info->status);
	else if (depth == 0)
		close(data->info->pipe[0].fd[1]);
	else if (depth != data->cmd_cnt - 1)
		close_pipe(data, depth);
	else if (depth == data->cmd_cnt - 1)
	{
		if (depth % 2 == 0)
			close(data->info->pipe[1].fd[0]);
		else
			close(data->info->pipe[0].fd[0]);
		i = -1;
		while (++i < data->cmd_cnt)
		{
			waitpid(data->info->pid[i], &data->info->status, 0);
			printf("pid[%d]: %d, status : %d\n", i, data->info->pid[i], WIFSIGNALED(data->info->status));
		}
	}
	if_signaled(data);
}

void	exec_process(t_data *data, t_list *cmdlist)
{
	int		depth;

	data->info = init_proc_info(data);
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
		data->info->pid[depth] = fork();
		if (data->info->pid[depth] > 0)
			parent_process(data, depth);
		else if (data->info->pid[depth] == 0)
			child_process(data, (t_list *)cmdlist->content, depth);
		else
			ft_perror("fork", errno);
		close_heredoc(data, (t_list *)cmdlist->content);
		cmdlist = cmdlist->next;
		depth++;
	}
}
