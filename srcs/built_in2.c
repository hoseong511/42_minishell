/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:57:34 by namkim            #+#    #+#             */
/*   Updated: 2022/08/22 12:42:02 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

extern int	g_status;

static void	update_pwd(char *keyform, char *value, t_data *data)
{
	char	*env;

	if (!keyform)
		return ;
	// if (ft_strncmp("PWD=", keyform, ft_strlen("PWD=") + 1) == 0)
	// {
	// 	env = match_env("PWD", data->envlist);
	// 	if (!env)
	// 		return ;
	// }
	env = ft_strjoin(keyform, value);
	if (!env)
		ft_error2("pwd", ": Malloc error\n");
	insert_env(env, data);
	free(env);
}

char	*ft_getpwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_error0("Couldn't get working directory\n");
	return (pwd);
}

void	ft_cd(char **args, t_data *data)
{
	char	*path;
	char	*pwd;

	pwd = ft_getpwd();
	if (!args[1])
		path = match_env("HOME", data->envlist);
	else
		path = args[1];
	if (chdir(path) == 0)
	{
		update_pwd("OLDPWD=", pwd, data);
		free(pwd);
		pwd = ft_getpwd();
		update_pwd("PWD=", pwd, data);
		free(pwd);
	}
	else
	{
		printf("cd: %s: No such file or directory\n", args[1]);
		g_status = 1;
	}
	free(path);//
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
