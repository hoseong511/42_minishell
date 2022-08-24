/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:26:17 by hossong           #+#    #+#             */
/*   Updated: 2022/08/24 17:55:29 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	ft_error(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
	exit(1);
}

void	ft_error3(char *arg, char *err_msg, int errcode)
{
	write(2, arg, ft_strlen(arg));
	write(2, err_msg, ft_strlen(err_msg));
	exit(errcode);
}

void	ft_perror(char *err_msg, int err)
{
	int	code;

	code = 1;
	write(2, "mini", 4);
	write(2, ": ", 2);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, ": ", 2);
	write(2, strerror(err), ft_strlen(strerror(err)));
	write(2, "\n", 1);
	if (err == ENOENT)
		code = 127;
	exit(code);
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		ft_perror("dup2", errno);
}

int	ft_syntax_error(t_type ttype, char *str)
{
	char	*format;
	char	*pipe;
	char	*none;

	format = "Syntax Error : syntax error near unexpected token ";
	pipe = "`|'";
	none = "`newline'";
	write(2, "mini: ", 6);
	write(2, format, ft_strlen(format));
	if (ttype == PIPE)
		write(2, pipe, ft_strlen(pipe));
	else if ((ttype > PIPE && ttype < R_ARG) && !str)
		write(2, none, ft_strlen(none));
	else if (ttype > PIPE && ttype < R_ARG)
		write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	g_status = 258;
	return (FALSE);
}
