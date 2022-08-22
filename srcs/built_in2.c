/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:57:34 by namkim            #+#    #+#             */
/*   Updated: 2022/08/22 19:38:28 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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

static void	ft_cd_error(char *arg)
{
	printf("cd: %s: No such file or directory\n", arg);
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
		update_pwd("OLDPWD=", pwd, data);
		free(pwd);
		pwd = ft_getpwd();
		update_pwd("PWD=", pwd, data);
		free(pwd);
	}
	else
		ft_cd_error(path);
	if (home == TRUE)
		free(path);
}
