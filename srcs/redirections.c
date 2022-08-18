/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:04:20 by namkim            #+#    #+#             */
/*   Updated: 2022/08/18 15:42:16 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

/*
redirection in
redirection out
redirection append
redirection heredoc
*/

void	redirection_in(char *filepath)
{
	int			fd;
	int			sign;
	struct stat	sb;

	if (!filepath)
		ft_error("Syntax Error\n");
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		sign = stat(filepath, &sb);
		if (sign == 0)
			printf("%s: %s\n", filepath, "Permission Denied");
		else
			printf("%s: %s", filepath, strerror(errno));
		exit(1);
	}
	else
	{
		dup2(fd, 0);
		close(fd);
	}
}

void	redirection_out(char *filepath)
{
	int		fd;

	if (!filepath)
		ft_error("Syntax Error\n");
	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("%s: %s", filepath, "Permission Denied");
		exit(1);
	}
	else
	{
		dup2(fd, 1);
		close(fd);
	}
}

void	redirection_append(char *filepath)
{
	int		fd;

	if (!filepath)
		ft_error("Syntax Error\n");
	fd = open(filepath, O_WRONLY | O_APPEND | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("%s: %s", filepath, "Permission Denied");
		exit(1);
	}
	else
	{
		dup2(fd, 1);
		close(fd);
	}
}
