/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:59:12 by namkim            #+#    #+#             */
/*   Updated: 2022/08/24 11:42:43 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	ft_built_in_error(char *arg1, char *arg2, char *errmsg)
{
	write(2, "mini\n", 4);
	write(2, ": ", 2);
	write(2, arg1, ft_strlen(arg1));
	write(2, ": ", 2);
	write(2, arg2, ft_strlen(arg2));
	write(2, " : ", 3);
	write(2, errmsg, ft_strlen(errmsg));
	g_status = 1;
}

static int	check_exit_args(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (ft_isdigit(arg[i]) == TRUE)
		i++;
	if (arg[i] == '\0')
		return (TRUE);
	else
		return (FALSE);
}

void	ft_exit(char **args, t_data *data)
{
	int	errcode;
	int	i;

	errcode = 0;
	i = 1;
	printf("exit\n");
	if (!args)
		exit(errcode);
	while (args[i])
	{
		if (check_exit_args(args[i]) == FALSE)
			ft_error3("exit", ": numeric argument required\n", 255);
		i++;
	}
	if (i > 2)
		ft_error3("exit", ": too many arguments\n", 1);
	else if (i == 2)
		errcode = ft_atoi(args[1]);
	set_termattr(data->save);
	exit(errcode);
}

static int	check_n_flag(char *flag)
{
	int	i;

	if (!flag)
		return (FALSE);
	i = 0;
	if (flag[i] == '-')
		i++;
	while (flag[i] == 'n')
		i++;
	if (flag[i] == '\0')
		return (TRUE);
	else
		return (FALSE);
}

void	ft_echo(char **args)
{
	int	nflag;

	nflag = FALSE;
	args++;
	if (!*args)
	{
		write(1, "\n", 1);
		g_status = 0;
		return ;
	}
	if (check_n_flag(*args))
	{
		nflag = TRUE;
		args++;
	}
	while (*args && *(args + 1))
	{
		write(1, *args, ft_strlen(*args));
		write(1, " ", 1);
		args++;
	}
	write(1, *args, ft_strlen(*args));
	if (nflag == FALSE)
		write(1, "\n", 1);
	g_status = 0;
}
