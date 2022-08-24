/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:09:37 by namkim            #+#    #+#             */
/*   Updated: 2022/08/24 15:31:02 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	**get_path(char **envlist)
{
	char	**res;
	char	*path_value;

	path_value = match_env("PATH", envlist);
	res = ft_split(path_value, ':');
	if (path_value)
		free(path_value);
	return (res);
}

char	*get_exe_format(char *path, char *cmd)
{
	char	*temp;
	char	*res;

	res = NULL;
	if ((!path && !cmd))
		return (NULL);
	if (!(*cmd))
	{
		res = ft_strdup(cmd);
		if (!res)
			ft_error("Malloc error\n");
		return (res);
	}
	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, cmd);
	free (temp);
	return (res);
}

static int	is_valid_exe_file(char *addr)
{
	struct stat	sb;
	int			sign;

	if (!addr)
		return (0);
	sign = stat(addr, &sb);
	if (sign == 0)
	{
		if ((sb.st_mode & S_IXUSR) != 0)
			return (TRUE);
		else
			return (-1);
	}
	return (-2);
}

char	*get_exe_file(char	**envp, char *cmd)
{
	char	*addr;
	int		i;
	int		sign;
	char	**path;

	i = 0;
	addr = NULL;
	path = get_path(envp);
	while (path && path[i])
	{
		addr = get_exe_format(path[i], cmd);
		sign = is_valid_exe_file(addr);
		if (sign == TRUE)
			return (addr);
		free(addr);
		addr = NULL;
		i++;
	}
	if (sign == -1)
		ft_error3(cmd, ": Permission Denied\n", 126);
	if (sign == -2)
		ft_error3(cmd, ": command not found\n", 127);
	addr = cmd;
	return (addr);
}
