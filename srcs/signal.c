/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:13:27 by namkim            #+#    #+#             */
/*   Updated: 2022/08/21 17:40:50 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"
/*
Ctrl + C : SIGINT - interactive / 실행 중 모두 exit status (1);
Ctrl + D :
	interactive의 경우 - 프롬프트에 글자가 남아있을 때 : 아무 문제 없음
	글자가 없을 때 : exit를 찍고 나간다(정상종료->exit status == 0)
	프로그램이 실행 중일 때 : 아무 작동 안하는 것 같음.
Ctrl+D is not a signal, it's EOF (End-Of-File).
It closes the stdin pipe. If read(STDIN) returns 0 (원래는 이렇다)
Ctrl + \ : do nothing : sigquit <- 이건 그냥 재우면 됨...!
대체 왜? g_exit_status가 필요하지?
자식프로세스가 부모프로세스에 오류를 전달하기 위해?
*/

extern int	g_status;

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		// rl_on_new_line();
		//printf("\033[");
		// printf("\n");
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
	{

	}
}

void	signal_handler_d(int signal)
{
	if (signal == SIGINT)
	{
		//g_status = 130; // <- 이걸 받을 수가 없다....
		printf("exit 55\n");
		exit(55);
	}
}

void	signal_handler_d2(int signo)
{
	if (signo == SIGINT)
	{
		g_status = 1; // <- 이걸 받을 수가 없다....
		printf("parent is back!\n");
		printf("mini-0.8$ \b\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	signal(SIGINT, signal_handler);	//안 되네 ㄸㄹㄹ
}
