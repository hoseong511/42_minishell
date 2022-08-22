/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_env1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:20:24 by namkim            #+#    #+#             */
/*   Updated: 2022/08/20 17:17:05 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

extern int	g_status;

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

static void	free_double_string(char *str1, char *str2)
{
	if (str1)
		free (str1);
	if (str2)
		free (str2);
}

char	*replace_key_to_value(char *str, int start, char *keystr, char **envp)
{
	char	*var;
	char	*prev;
	char	*next;
	char	*res;

	res = NULL;
	var = ft_strnstr(str + start, keystr, ft_strlen(str));
	if (var)
	{
		prev = ft_strndup(str, var - str - 1);
		next = ft_strdup(var + ft_strlen(keystr));
		if (*keystr == '?')
			var = ft_itoa(g_status);
		else
			var = match_env(keystr, envp);
		if (var)
		{
			res = ft_strjoin(prev, var);
			free_double_string(prev, var);
			prev = res;
			res = ft_strjoin(prev, next);
		}
		else
			res = ft_strjoin(prev, next);
		free_double_string(prev, next);
	}
	return (res);
}
