/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:26:17 by hossong           #+#    #+#             */
/*   Updated: 2022/08/18 15:16:48 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	ft_error(char *err_msg)
{
	write(1, err_msg, ft_strlen(err_msg));
	exit(1);
}

void	ft_perror(char *err_msg, int err)
{
	printf("%s : %s", err_msg, strerror(err));
	exit(1);
}
