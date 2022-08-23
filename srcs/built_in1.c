/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:54:24 by namkim            #+#    #+#             */
/*   Updated: 2022/08/23 13:44:15 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	insert_env(char *arg, t_data *data)
{
	int		len;
	int		idx;
	char	*key;

	len = get_env_len(arg);
	if (len == 0)
		ft_built_in_error("export", arg, "not a valid identifier\n");
	if (arg[len] == '=')
	{
		key = ft_strndup(arg, len);
		idx = get_env_idx(key, data->envlist);
		if (idx >= 0)
		{
			free(data->envlist[idx]);
			data->envlist[idx] = ft_strdup(arg);
		}
		else
			add_env_to_envlist(arg, data);
		free(key);
		return (TRUE);
	}
	else
		return (FALSE);
}

void	ft_export(char **args, t_data *data)
{
	int		i;

	i = 1;
	if (!args[i])
		ft_env(args, data);
	while (args[i])
	{
		insert_env(args[i], data);
		if (g_status == 1)
			return ;
		i++;
	}
	g_status = 0;
}

void	ft_env(char **args, t_data *data)
{
	char	**envp;

	envp = data->envlist;
	if (args[1])
	{
		if (args[0][1] == 'n')
			printf("env: %s: Unnecessary Argument\n", args[1]);
		g_status = 1;
		return ;
	}
	if (!envp)
		return ;
	while (*envp)
	{
		if (args[0][1] == 'x')
			printf("declare -x ");
		printf("%s\n", *envp++);
	}
	g_status = 0;
}

void	ft_unset(char **args, t_data *data)
{
	int		i;
	char	**envp;
	int		idx;

	i = 1;
	envp = data->envlist;
	while (args[i])
	{
		idx = get_env_idx(args[i], data->envlist);
		if (idx >= 0)
		{
			free (envp[idx]);
			envp[idx] = envp[data->envlist_cnt - 1];
			envp[data->envlist_cnt - 1] = NULL;
			data->envlist_cnt--;
		}
		i++;
	}
	g_status = 0;
}

void	ft_pwd(char **args)
{
	char	*res;

	if (!args || !args[0])
		return ;
	else
	{
		res = getcwd(NULL, 0);
		if (!res)
		{
			printf("Couldn't get working directory\n");
			g_status = 1;
		}
		printf("%s\n", res);
		free(res);
	}
	g_status = 0;
}
