/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:57:34 by namkim            #+#    #+#             */
/*   Updated: 2022/08/20 20:53:38 by hossong          ###   ########.fr       */
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
			ft_error("Couldn't get working directory\n");
		path = ft_strjoin("PWD=", pwd);
		insert_env(path, data);
		free(pwd);
		free(path);
	}
	else
	{
		printf("cd: %s: No such file or directory\n", args[1]);
		exit(1);
	}
}

void	ft_exit(void)
{
	printf("exit\n");
	g_status = 1;
	exit(0);
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
