/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:26:17 by hossong           #+#    #+#             */
/*   Updated: 2022/08/19 02:07:09 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	ft_error(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
	exit(1);
}

void	ft_error2(char *arg, char *err_msg)
{
	write(2, arg, ft_strlen(arg));
	write(2, err_msg, ft_strlen(err_msg));
	exit(1);
}

void	ft_perror(char *err_msg, int err)
{
	write(2, err_msg, ft_strlen(err_msg));
	write(2, strerror(err), ft_strlen(strerror(err)));
	write(2, "\n", 1);
	exit(1);
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		ft_perror("dup2: ", errno);
}
