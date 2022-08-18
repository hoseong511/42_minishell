/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_excution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:27:01 by hossong           #+#    #+#             */
/*   Updated: 2022/08/18 13:27:09 by hossong          ###   ########.fr       */
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

void	exec_process(t_data *data, t_list *cmdlist)
{
	int	depth;

	data->info = init_info();
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
		exec_builtin((t_list *)cmdlist->content, is_built);
	else
		exec_process(data, cmdlist);
	data->cmd_cnt = 0;
}
