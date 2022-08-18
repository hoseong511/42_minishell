/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:38:07 by hossong           #+#    #+#             */
/*   Updated: 2022/08/18 19:38:20 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_pipe(t_proc *info, int depth, int cnt)
{
	if (depth % 2 == 0 && pipe(info->pipe[0].fd) != 0)
		ft_perror("pipe", errno);
	else if (cnt > 2 && (depth % 2 && pipe(info->pipe[1].fd) != 0))
		ft_perror("pipe", errno);
}

void	pipe_io(t_proc *info, int depth, int cmd_cnt)
{
	if (cmd_cnt > 1)
	{
		if (depth % 2 == 0)
			close(info->pipe[0].fd[0]);
		else if (cmd_cnt > 2 && depth % 2)
			close(info->pipe[1].fd[0]);
	}
}
