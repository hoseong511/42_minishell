/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:28:21 by hossong           #+#    #+#             */
/*   Updated: 2022/08/19 17:07:00 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*gnl(int fd, int depth)
{
	char	*des;
	char	buff;
	char	byte;

	buff = 0;
	byte = read(fd, &buff, 1);
	if (byte < 0 || (byte == 0 && depth == 0))
		return (NULL);
	if (byte == 0 || buff == '\n')
		des = malloc(depth + 2);
	else
		des = gnl(fd, depth + 1);
	if (des)
	{
		des[depth] = buff;
		des[depth + 1] = des[depth + 1] * (buff != '\n');
	}
	return (des);
}

char	*get_next_line(int fd)
{
	return (gnl(fd, 0));
}
