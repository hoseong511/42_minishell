/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:57:34 by namkim            #+#    #+#             */
/*   Updated: 2022/08/20 12:57:59 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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

//여기서 모든 메모리 해제를 넣어줘야 하는지...? 어차피 exit가 모두 처리할건데도?
void	ft_exit(void)	//argument?
{
//	(void) data;
	printf("exit\n");
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
