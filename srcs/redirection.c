/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:38:07 by hossong           #+#    #+#             */
/*   Updated: 2022/08/18 17:00:43 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	settings_redirection(void)
{
	printf("settings_redirection\n");
}

void	redirection(void)
{
	printf("redirection\n");
	settings_redirection();
}

void	init_pipe(t_proc *info, int depth, int cnt)
{
	if (depth % 2 == 0 && pipe(info->pipe[0].fd) != 0)
		ft_perror("pipe", errno);
	else if (cnt > 2 && (depth % 2 && pipe(info->pipe[1].fd) != 0))
		ft_perror("pipe", errno);
}
