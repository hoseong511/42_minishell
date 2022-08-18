/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_excution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:27:01 by hossong           #+#    #+#             */
/*   Updated: 2022/08/18 13:47:30 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	excute_cmd(void)
{
	printf("excute_cmd\n");
}

void	exec_process(t_data *data, t_list *cmdlist)
{
	int	depth;

	data->info = init_proc_info();
	depth = 0;
	while (cmdlist && depth < data->cmd_cnt)
	{
		data->info->pid = fork();
		if (data->cmd_cnt > 1)
			init_pipe(data->info, depth);
		if (data->info->pid > 0)
			parent_process(data, depth);
		else if (data->info->pid == 0)
			child_process(data, (t_list *)cmdlist->content, depth);
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
		exec_builtin((t_list *)cmdlist->content);
	else
		exec_process(data, cmdlist);
	data->cmd_cnt = 0;
}
