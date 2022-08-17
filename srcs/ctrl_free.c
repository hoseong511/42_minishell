/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:27:38 by hossong           #+#    #+#             */
/*   Updated: 2022/08/16 20:32:21 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	free_cmd(t_list *cmdlist, char *tar)
{
	if (ft_strncmp(tar, "t_cmd", 6) == 0)
	{
		free(((t_cmd *)cmdlist->content)->str);
		free(cmdlist->content);
	}
	else if (ft_strncmp(tar, "t_cmd2", 7) == 0)
	{
		free(((t_cmd2 *)cmdlist->content)->str);
		free(cmdlist->content);
	}
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_cmd_content(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free_str(((t_cmd2 *)lst->content)->str);
		free(lst->content);
		free(lst);
		lst = tmp;
	}
	free(lst->content);
}

void	free_cmdlist(t_list *cmdlist)
{
	t_list	*tmp;

	while (cmdlist)
	{
		tmp = cmdlist->next;
		free_cmd_content((t_list *)cmdlist->content);
		free(cmdlist);
		cmdlist = tmp;
	}
}

void	free_tokenlist(t_data *data)
{
	t_list	*tmp;

	while (data->tokenlist)
	{
		tmp = data->tokenlist->next;
		free(((t_cmd *)data->tokenlist->content)->str);
		free(data->tokenlist->content);
		free(data->tokenlist);
		data->tokenlist = tmp;
	}
}

void	free_data(t_data *data)
{
	t_list	*tmp;

	while (data->envlist)
	{
		tmp = data->envlist->next;
		free(((t_env *)data->envlist->content)->key);
		free(((t_env *)data->envlist->content)->value);
		free(data->envlist->content);
		free(data->envlist);
		data->envlist = tmp;
	}
	free(data);
}
