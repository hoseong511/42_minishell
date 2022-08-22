/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:34:31 by hossong           #+#    #+#             */
/*   Updated: 2022/08/22 21:57:37 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	close_heredoc(t_data *data, t_list *arglist)
{
	t_cmd2	*arg;
	int		i;

	if (data->heredoc && arglist == NULL)
	{
		i = 0;
		while (data->heredoc[i] == -1)
			i++;
		close(data->heredoc[i]);
		data->heredoc[i] = -1;
	}
	while (arglist)
	{
		arg = (t_cmd2 *)arglist->content;
		if (arg->type == R_HEREDOC)
		{
			i = 0;
			while (data->heredoc[i] == -1)
				i++;
			close(data->heredoc[i]);
			data->heredoc[i] = -1;
		}
		arglist = arglist->next;
	}
}

int	count_heredoc(t_list *cmdlist)
{
	t_list	*arglist;
	t_cmd2	*arg;
	int		cnt;

	cnt = 0;
	while (cmdlist)
	{
		arglist = (t_list *)cmdlist->content;
		while (arglist)
		{
			arg = (t_cmd2 *)arglist->content;
			if (arg->type == R_HEREDOC)
				cnt++;
			arglist = arglist->next;
		}
		cmdlist = cmdlist->next;
	}
	if (!cnt)
		return (0);
	return (cnt);
}

int	set_heredoc(t_data *data, t_list *cmdlist)
{
	t_list	*arglist;
	t_cmd2	*arg;
	int		i;

	i = 0;
	while (cmdlist)
	{
		arglist = (t_list *)cmdlist->content;
		while (arglist)
		{
			arg = (t_cmd2 *)arglist->content;
			if (arg->type == R_HEREDOC)
			{
				redirection_heredoc(data, arg->str[1], i);
				if (g_status == 1)
					return (-1);
				i++;
			}
			arglist = arglist->next;
		}
		cmdlist = cmdlist->next;
	}
	return (0);
}

int	heredoc(t_data *data)
{
	int	cnt;

	cnt = count_heredoc(data->cmdlist);
	if (cnt == 0)
		return (0);
	data->heredoc = (int *)malloc(sizeof(int) * (cnt + 1));
	if (!data->heredoc)
		ft_perror("Malloc", errno);
	data->heredoc[cnt] = -2;
	if (set_heredoc(data, data->cmdlist) == -1)
		return (-1);
	return (0);
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
