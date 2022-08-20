/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_envlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:40:01 by namkim            #+#    #+#             */
/*   Updated: 2022/08/19 17:21:37 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	is_envlist_full(t_data *data)
{
	if (data->envlist_cnt == data->envlist_size)
		return (TRUE);
	else
		return (FALSE);
}

int	add_env_to_envlist(char *env, t_data *data)
{
	char	**new_envlist;

	if (!env)
		return (FALSE);
	if (is_envlist_full(data))
	{
		new_envlist = \
				ft_calloc(data->envlist_size + 10, sizeof(char *));
		if (!new_envlist)
			ft_error("Malloc error while add env\n");
		ft_memcpy(new_envlist, data->envlist, \
						sizeof(char *) * data->envlist_cnt);
		free(data->envlist);
		data->envlist = new_envlist;
		data->envlist_size += 10;
	}
	data->envlist[data->envlist_cnt] = ft_strdup(env);//복제해서 넣는다
	(data->envlist_cnt)++;
	return (TRUE);
}

//만약 존재하면 idx return, 존재하지 않으면 -1
int	get_env_idx(char *keystr, char **envp)
{
	int	idx;
	int	key_len;

	idx = 0;
	if (!envp)
		return (-1);
	key_len = ft_strlen(keystr);
	while (envp[idx])
	{
		if (ft_strncmp(keystr, envp[idx], key_len) == 0)
		{
			if (envp[idx][key_len] == '=')
				return (idx);
		}
		idx++;
	}
	return (-1);
}
