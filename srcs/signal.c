/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:13:27 by namkim            #+#    #+#             */
/*   Updated: 2022/08/16 22:21:32 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"
/*
Ctrl + C : SIGINT
Ctrl + D : exit shell... exit shell 하는 건 너무 많은데..?ㅠㅠ
Ctrl+D is not a signal, it's EOF (End-Of-File).
It closes the stdin pipe. If read(STDIN) returns 0 (원래는 이렇다)
Ctrl + \ : do nothing
*/
