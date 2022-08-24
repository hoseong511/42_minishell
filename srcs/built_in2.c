/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:57:34 by namkim            #+#    #+#             */
/*   Updated: 2022/08/24 11:42:07 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	update_pwd(char *keyform, char **value, t_data *data)
{
	char	*env;

	if (!keyform)
		return ;
	env = ft_strjoin(keyform, *value);
	if (!env)
		ft_error3("pwd", ": Malloc error\n", 1);
	insert_env(env, data);
	free(env);
	free(*value);
}

char	*ft_getpwd(void)
{
	char	*pwd;
	char	*err_msg;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		err_msg = "Couldn't get working directory\n";
		write(2, err_msg, ft_strlen(err_msg));
		g_status = 1;
		return (NULL);
	}
	g_status = 0;
	return (pwd);
}

static void	ft_cd_error(char *arg, char **pwd)
{
	write(2, "mini: ", 6);
	write(2, "cd: ", 4);
	if (arg)
		write(2, arg, ft_strlen(arg));
	if (*pwd)
		free (*pwd);
	if (!arg)
		write(2, "HOME not set\n", \
				ft_strlen("HOME not set\n"));
	else
		write(2, " : No such file or directory\n", \
				ft_strlen(" : No such file or directory\n"));
	g_status = 1;
}

void	ft_cd(char **args, t_data *data)
{
	char	*path;
	char	*pwd;
	int		home;

	pwd = ft_getpwd();
	home = FALSE;
	if (!args[1])
	{
		path = match_env("HOME", data->envlist);
		home = TRUE;
	}
	else
		path = args[1];
	if (chdir(path) == 0)
	{
		update_pwd("OLDPWD=", &pwd, data);
		pwd = ft_getpwd();
		update_pwd("PWD=", &pwd, data);
		g_status = 0;
	}
	else
		ft_cd_error(path, &pwd);
	if (home == TRUE && path)
		free(path);
}
