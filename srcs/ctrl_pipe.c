/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:38:07 by hossong           #+#    #+#             */
/*   Updated: 2022/08/19 00:20:57 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_pipe(t_data *data, int depth, int cnt)
{
	if (cnt < 2)
		return ;
	if (depth % 2 == 0 && pipe(data->pipe.fd0) != 0)
		ft_perror("pipe", errno);
	else if (cnt > 2 && (depth % 2 && pipe(data->pipe.fd1) != 0))
		ft_perror("pipe", errno);
}

void	pipe_io(t_data *data, int depth, int cmd_cnt)
{
	if (cmd_cnt < 2)
		return ;
	if (depth != cmd_cnt - 1)
	{
		if (depth % 2 == 0)
		{
			close(data->pipe.fd0[0]);
			printf("depth : %d hi\n",depth);
			if (dup2(data->pipe.fd0[1], 1))
				ft_error("error\n");
		}
		else
		{
			close(data->pipe.fd1[0]);
			dup2(data->pipe.fd1[1], 1);
		}
	}
	else
	{
		if (depth % 2 == 0)
		{
			dup2(data->pipe.fd1[0], 0);
			close(data->pipe.fd1[0]);
		}
		else
		{
			printf("depth : %d hi\n",depth);
			dup2(data->pipe.fd0[0], 0);
			close(data->pipe.fd0[0]);
		}
	}
}
