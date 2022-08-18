/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:38:07 by hossong           #+#    #+#             */
/*   Updated: 2022/08/18 17:24:16 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_pipe(t_proc *info, int depth)
{
	if (depth % 2 == 0 && pipe(info->pipe[0].fd) != 0)
		ft_perror("pipe", errno);
	else if (depth % 2 && pipe(info->pipe[1].fd) != 0)
		ft_perror("pipe", errno);
}
