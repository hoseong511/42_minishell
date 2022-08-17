/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_excution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:27:01 by hossong           #+#    #+#             */
/*   Updated: 2022/08/17 19:31:36 by hossong          ###   ########.fr       */
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
	sleep(1);
	exit(1);
}

void	do_parent_proc(t_data *data, int depth)
{
	int	status;

	(void)data;
	(void)depth;
	wait(&status);
	printf("parent, exit_status : %d\n", WEXITSTATUS(status));
}

void	execution(t_data *data)
{
	t_list	*cmdlist;
	t_proc	*info;
	int		depth;

	info = (t_proc *)malloc(sizeof(t_proc));
	if (!info)
		ft_error("ERROR: Malloc Error\n");
	ft_memset(info, 0, sizeof(t_proc));
	data->info = info;
	cmdlist = data->cmdlist;
	depth = 0;
	while (cmdlist && depth < data->cmd_cnt)
	{
		info->pid = fork();
		if (depth == 0 && pipe(info->pipe[0].fd))
			ft_perror("pipe", errno);
		if (info->pid > 0)
			do_parent_proc(data, depth);
		else if (info->pid == 0)
			do_child_proc(data, (t_list *)cmdlist->content, depth);
		else
			ft_perror("fork error", errno);
		cmdlist = cmdlist->next;
		depth++;
	}
}
