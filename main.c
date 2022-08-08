/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:42:28 by hossong           #+#    #+#             */
/*   Updated: 2022/08/08 15:30:24 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_list	*idx_cmd(t_list *cmd, int idx)
{
	t_list	*node;

	node = cmd;
	while (node && node->idx != idx)
		node = node->next;
	if (node && node->idx == idx)
		return (node);
	return (NULL);
}

void	parse_envp(t_data *data, char **envp)
{
	char	*tar;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strnstr(envp[i], "PATH", ft_strlen("PATH")))
			continue ;
		tar = ft_strtrim(envp[i], "PATH=");
		data->dir = ft_split(tar, ':');
		free(tar);
		break ;
	}
}

char	*search_cmd_path(t_data *data, int idx)
{
	char	*path;
	int		i;
	char	*tmp;
	char	*cmd;

	if (cmd && ft_strrchr(cmd, '/'))
	{
		if (access(cmd, R_OK) == -1)
			err_error(cmd, 127);
		cmd = ft_strrchr(cmd, '/');
	}
	i = -1;
	while (data->dir[++i])
	{
		tmp = ft_strjoin(data->dir[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) != -1)
			break ;
		free(path);
	}
	if (!data->dir[i])
		return (NULL);
	return (path);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	*pwd_name;
	pid_t	pid;
	char	name[BUF_SIZE];
	char	**line;

	(void)argc;
	(void)argv;
	(void)envp;
	printf("==minishell==\n");
	while (1)
	{
		str = readline("mini-0.1$ ");
		if (ft_strstr(str, INHIBIT))
		{
			printf("inhibit\n");
			continue ;
		}
		if (ft_strchr(str, '|'))
		{
			line = ft_split(str, '|');
			int i = 0;
			while (i < 2)
			{
				char **arg;
				if (i == 0)
				{
					arg = ft_split(line[0], ' ');
					pid = fork();
					if (pid == 0)
					{
						execve("/bin/echo", arg, envp);
						printf("%s\n", strerror(errno));
					}
					else if (pid < 0)
						printf("%d, %s\n", errno, strerror(errno));
					else
						wait(NULL);
				}
				else
				{
					arg = ft_split(line[1], ' ');
					pid = fork();
					if (pid == 0)
					{
						execve("/usr/bin/grep", arg, envp);
						printf("%s\n", strerror(errno));
					}
					else if (pid < 0)
						printf("%d, %s\n", errno, strerror(errno));
					else
						wait(NULL);
				}
				i++;
			}
		}
		else
			line = ft_split(str, ' ');
		if (*str)
			add_history(str);
		if (ft_strncmp(line[0], "exit\0", 5) == 0)
		{
			printf("exit\n");
			break ;
		}
		else if (ft_strncmp(line[0], "pwd\0", 4) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				pwd_name = getcwd(name, BUF_SIZE);
				if (pwd_name)
				{
					printf("%s\n", pwd_name);
					exit(0);
				}
				printf("%d, %s\n", errno, strerror(errno));
			}
			else if (pid < 0)
				printf("%d, %s\n", errno, strerror(errno));
			else
				wait(NULL);
		}
		else if (ft_strncmp(line[0], "echo\0", 5) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execve("/bin/echo", line, envp);
				printf("%s\n", strerror(errno));
			}
			else if (pid < 0)
				printf("%d, %s\n", errno, strerror(errno));
			else
				wait(NULL);
		}
		free(str);
	}
	return (0);
}
