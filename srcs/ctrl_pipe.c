/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:38:07 by hossong           #+#    #+#             */
/*   Updated: 2022/08/19 02:08:05 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_pipe(t_data *data, int depth, int cnt)
{
	if (cnt < 2)
		return ;
	if (depth % 2 == 0 && pipe(data->info->pipe[0].fd) != 0)
		ft_perror("pipe", errno);
	else if (cnt > 2 && (depth % 2 && pipe(data->info->pipe[1].fd) != 0))
		ft_perror("pipe", errno);
}

void	pipe_io(t_data *data, int depth, int cmd_cnt)
{
	if (cmd_cnt < 2)
		return ;
	else if (depth == 0)
		ft_dup2(data->info->pipe[0].fd[1], 1);
	else if (depth != cmd_cnt - 1)
	{
		if (depth % 2 == 0)
		{
			ft_dup2(data->info->pipe[1].fd[0], 0);
			ft_dup2(data->info->pipe[0].fd[1], 1);
		}
		else
		{
			ft_dup2(data->info->pipe[0].fd[0], 0);
			ft_dup2(data->info->pipe[1].fd[1], 1);
		}
	}
	else
	{
		if (depth % 2 == 0)
			ft_dup2(data->info->pipe[1].fd[0], 0);
		else
			ft_dup2(data->info->pipe[0].fd[0], 0);
	}
}
