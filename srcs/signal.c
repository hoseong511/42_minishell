/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:13:27 by namkim            #+#    #+#             */
/*   Updated: 2022/08/21 20:01:16 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

extern int	g_status;

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("mini-0.8$ \b\n");
		g_status = 1;
	}
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	signal_handler_c(int signal)
{
	if (signal == SIGINT)
		;
}

void	signal_handler_d(int signal)
{
	if (signal == SIGINT)
	{
		printf("exit 55\n");
		exit(55);
	}
}
