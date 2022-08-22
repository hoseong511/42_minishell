/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 00:19:19 by hossong           #+#    #+#             */
/*   Updated: 2022/08/23 02:09:18 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	child_heredoc(t_data *data, char *end_of_file, int p_fd[])
{
	char	*str;

	while (1)
	{
		signal(SIGINT, signal_handler_d);
		str = readline("> ");
		do_expansion(&str, data->envlist, '"');
		if (ft_strncmp(str, end_of_file, ft_strlen(end_of_file) + 1) == 0)
			exit(0);
		write(p_fd[1], str, ft_strlen(str));
		write(p_fd[1], "\n", 1);
		free (str);
	}
}

static int	parent_heredoc(t_data *data, pid_t pid, int p_fd[], int idx)
{
	int	ret;

	signal(SIGINT, signal_handler_c);
	ret = 0;
	if (waitpid(pid, &data->info->status, 0) == -1)
		ft_perror("wait", errno);
	if (WEXITSTATUS(data->info->status))
	{
		close(p_fd[1]);
		close(p_fd[0]);
		g_status = WEXITSTATUS(data->info->status);
		ret = -1;
	}
	else
	{
		close(p_fd[1]);
		data->heredoc[idx] = dup(p_fd[0]);
		close(p_fd[0]);
	}
	return (ret);
}

int	redirection_heredoc(t_data *data, char *end_of_file, int idx)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		ft_perror("Pipe", errno);
	pid = fork();
	if (pid > 0)
	{
		if (parent_heredoc(data, pid, p_fd, idx) == -1)
			return (-1);
	}
	else if (pid == 0)
		child_heredoc(data, end_of_file, p_fd);
	else
		ft_perror("fork", errno);
	return (0);
}
