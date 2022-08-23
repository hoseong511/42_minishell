/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_heredoc1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:34:31 by hossong           #+#    #+#             */
/*   Updated: 2022/08/23 15:19:09 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	close_heredoc(t_data *data, t_list *arglist)
{
	int		i;

	i = 0;
	while (data->heredoc && arglist == NULL)
	{
		while (data->heredoc[i] == -1)
			i++;
		if (data->heredoc[i] == -2)
			return ;
		close(data->heredoc[i]);
		data->heredoc[i] = -1;
	}
	while (arglist)
	{
		if (((t_cmd2 *)arglist->content)->type == R_HEREDOC)
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
				if (redirection_heredoc(data, arg->str[1], i) == -1)
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
	ft_memset(data->heredoc, 0, sizeof(int *));
	data->heredoc[cnt] = -2;
	if (set_heredoc(data, data->cmdlist) == -1)
		return (-1);
	return (0);
}
