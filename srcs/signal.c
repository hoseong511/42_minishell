/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:13:27 by namkim            #+#    #+#             */
/*   Updated: 2022/08/19 15:09:26 by namkim           ###   ########.fr       */
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
