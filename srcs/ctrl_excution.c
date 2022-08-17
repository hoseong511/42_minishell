/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_excution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:27:01 by hossong           #+#    #+#             */
/*   Updated: 2022/08/18 01:01:10 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	settings_redirection(void)
{
	printf("settings_redirection\n");
}

void	redirection(void)
{
	printf("redirection\n");
	settings_redirection();
}

void	excute_cmd(void)
{
	printf("excute_cmd\n");
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

void	init_pipe(t_proc *info, int depth)
{
	if (depth % 2 == 0 && pipe(info->pipe[0].fd) != 0)
		ft_perror("pipe", errno);
	else if (depth % 2 && pipe(info->pipe[1].fd) != 0)
		ft_perror("pipe", errno);
}

t_proc	*init_info(void)
{
	t_proc	*new;

	new = (t_proc *)malloc(sizeof(t_proc));
	if (!new)
		ft_error("ERROR: Malloc Error\n");
	ft_memset(new, 0, sizeof(t_proc));
	return (new);
}

void	execution(t_data *data)
{
	t_list	*cmdlist;
	int		depth;

	data->info = init_info();
	cmdlist = data->cmdlist;
	depth = 0;
	while (cmdlist && depth < data->cmd_cnt)
	{
		data->info->pid = fork();
		if (data->cmd_cnt > 1)
			init_pipe(data->info, depth);
		if (data->info->pid > 0)
			do_parent_proc(data, depth);
		else if (data->info->pid == 0)
			do_child_proc(data, (t_list *)cmdlist->content, depth);
		else
			ft_perror("fork error", errno);
		cmdlist = cmdlist->next;
		depth++;
	}
	data->cmd_cnt = 0;
}
