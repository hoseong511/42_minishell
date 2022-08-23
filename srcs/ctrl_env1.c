/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_env1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:20:24 by namkim            #+#    #+#             */
/*   Updated: 2022/08/22 21:04:54 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	is_valid_env_name(char c, int idx)
{
	if (ft_isdigit(c))
	{
		if (idx == 0)
			return (FALSE);
		else
			return (TRUE);
	}
	if (ft_isalpha(c))
		return (TRUE);
	if (c == '_')
		return (TRUE);
	return (FALSE);
}

char	**make_envlist(char **envp, t_data *data)
{
	int		list_size;
	char	**res;

	list_size = 0;
	res = NULL;
	while (envp[list_size])
		list_size++;
	res = (char **)malloc(sizeof(char *) * (list_size + 1));
	if (!res)
		ft_perror("Malloc", errno);
	data->envlist_size = list_size;
	return (res);
}

char	**get_env(char **envp, t_data *data)
{
	int		i;
	char	**res;

	i = 0;
	res = make_envlist(envp, data);
	while (i < data->envlist_size)
	{
		res[i] = ft_strdup(envp[i]);
		if (!res[i])
		{
			while (i-- > 0)
				free(res[i]);
			free(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	data->envlist_cnt = data->envlist_size;
	return (res);
}

char	*match_env(char *keystr, char **envlist)
{
	int		i;
	int		key_len;
	int		sign;
	char	*res;

	if (!keystr || !envlist)
		return (NULL);
	i = 0;
	sign = -1;
	key_len = ft_strlen(keystr);
	while (envlist[i])
	{
		sign = ft_strncmp(keystr, envlist[i], key_len);
		if (sign == 0)
		{
			if (envlist[i][key_len] == '=')
			{
				res = ft_strdup(ft_strchr(envlist[i], '=') + 1);
				return (res);
			}
		}
		i++;
	}
	return (NULL);
}

int	count_env(char *str, char chr)
{
	int		i;
	int		len;
	int		res;
	int		slen;

	res = 0;
	i = 0;
	slen = ft_strlen(str);
	while (i < slen && str[i])
	{
		if (str[i] == '$')
		{
			i++;
			len = get_env_len(str + i);
			if (len != 0)
			{
				res++;
				i += len - 1;
			}
		}
		else if (chr != '\"' && str[i] == '\'')
			i = get_quote_end_idx(str, i);
		i++;
	}
	return (res);
}
