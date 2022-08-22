/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:57:34 by namkim            #+#    #+#             */
/*   Updated: 2022/08/22 10:25:24 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

extern int	g_status;

void	ft_cd(char **args, t_data *data)
{
	char	*path;
	char	*pwd;
	int		sign;

	if (!args[1])
		path = match_env("HOME", data->envlist);
	else
		path = args[1];
	sign = chdir(path);
	if (sign == 0)
	{
		free(path);
		pwd = getcwd(NULL, 0);
		if (!pwd)
			ft_error0("Couldn't get working directory\n");
		path = ft_strjoin("PWD=", pwd);
		insert_env(path, data);
		free(pwd);
		free(path);
	}
	else
	{
		printf("cd: %s: No such file or directory\n", args[1]);
		g_status = 1;
	}
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

void	ft_exit(char **args)
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
		ft_error2("exit", ": too many arguments\n");
	else if (i == 2)
		errcode = ft_atoi(args[1]);
	exit(errcode);
}

void	ft_echo(char **args)
{
	int	i;

	i = 1;
	if (ft_strncmp(args[i], "-n", 3) == 0)
		i++;
	while (args[i + 1])
	{
		write(1, args[i], ft_strlen(args[i]));
		write(1, " ", 1);
		i++;
	}
	write(1, args[i], ft_strlen(args[i]));
	if (ft_strncmp(args[1], "-n", 3) != 0)
		write(1, "\n", 1);
}
