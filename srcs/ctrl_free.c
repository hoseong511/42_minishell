/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:27:38 by hossong           #+#    #+#             */
/*   Updated: 2022/08/14 17:28:27 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	free_cmdlist(t_data *data)
{
	t_list	*tmp;
	int		i;

	while (data->cmdlist)
	{
		tmp = data->cmdlist->next;
		i = 0;
		while (((t_cmd2 *)data->cmdlist->content)->str[i])
		{
			free(((t_cmd2 *)data->cmdlist->content)->str[i]);
			i++;
		}
		free(((t_cmd2 *)data->cmdlist->content)->str);
		free(data->cmdlist->content);
		free(data->cmdlist);
		data->cmdlist = tmp;
	}
}

void	free_tokenlist(t_data *data)
{
	t_list	*tmp;

	while (data->tokenlist)
	{
		tmp = data->tokenlist->next;
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