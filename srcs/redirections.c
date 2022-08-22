/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:04:20 by namkim            #+#    #+#             */
/*   Updated: 2022/08/22 11:05:44 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

extern int	g_status;

void	redirection_in(char *filepath)
{
	int			fd;
	int			sign;
	struct stat	sb;

	if (!filepath)
		ft_error("Syntax Error\n");
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		sign = stat(filepath, &sb);
		if (sign == 0)
			printf("%s: %s\n", filepath, "Permission Denied");
		else
			printf("%s: %s\n", filepath, strerror(errno));
		exit(1);
	}
	else
	{
		if (dup2(fd, 0) < 0)
			ft_perror("Dup2", errno);
		close(fd);
	}
}

void	redirection_out(char *filepath)
{
	int		fd;

	if (!filepath)
		ft_error("Syntax Error\n");
	fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("%s: %s\n", filepath, "Permission Denied");
		exit(1);
	}
	else
	{
		if (dup2(fd, 1) < 0)
			ft_perror("Dup2", errno);
		close(fd);
	}
}

void	redirection_append(char *filepath)
{
	int		fd;

	if (!filepath)
		ft_error("Syntax Error\n");
	fd = open(filepath, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("%s: %s\n", filepath, "Permission Denied");
		exit(1);
	}
	else
	{
		if (dup2(fd, 1) < 0)
			ft_perror("Dup2", errno);
		close(fd);
	}
}

void	redirection_heredoc(t_data *data, char *end_of_file, int idx)
{
	int		p_fd[2];
	char	*str;
	pid_t	pid;

	pipe(p_fd);
	pid = fork();
	while (pid == 0)
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
	if (pid > 0)
	{
		signal(SIGINT, signal_handler_c);
		waitpid(pid, &data->info->status, 0);
		if (WEXITSTATUS(data->info->status) == 1)
		{
			close(p_fd[1]);
			close(p_fd[0]);
			g_status = WEXITSTATUS(data->info->status);
			signal(SIGINT, signal_handler);
		}
		else
		{
			close(p_fd[1]);
			data->heredoc[idx] = dup(p_fd[0]);
			close(p_fd[0]);
		}
	}
}

t_list	*redirection_left(t_data *data, t_list *args)
{
	t_list	*node;
	t_type	node_type;
	int		idx;

	node = args;
	while (node)
	{
		node_type = ((t_cmd2 *)node->content)->type;
		if (node_type < R_IN || node_type == R_OUT || node_type == R_APPD)
			return (node);
		else if (node_type == R_IN)
			redirection_in(((t_cmd2 *)node->content)->str[1]);
		else if (node_type == R_HEREDOC)
		{
			idx = 0;
			while (data->heredoc[idx] == -1)
				idx++;
			ft_dup2(data->heredoc[idx], 0);
			close(data->heredoc[idx]);
			data->heredoc[idx] = -1;
		}
		node = node->next;
		data->redir = 1;
	}
	return (node);
}

t_list	*redirection_right(t_list *args)
{
	t_list	*node;
	t_type	node_type;

	node = args;
	while (node)
	{
		node_type = ((t_cmd2 *)node->content)->type;
		if (node_type < R_IN)
			return (node);
		else if (node_type == R_OUT)
			redirection_out(((t_cmd2 *)node->content)->str[1]);
		else if (node_type == R_APPD)
			redirection_append(((t_cmd2 *)node->content)->str[1]);
		node = node->next;
	}
	return (node);
}
