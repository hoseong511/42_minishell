/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:20:24 by namkim            #+#    #+#             */
/*   Updated: 2022/08/17 18:05:03 by namkim           ###   ########.fr       */
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

// t_list	*get_env(char **envp)//
// {
// 	int		i;
// 	char	**line;
// 	t_list	*result;
// 	t_list	*new;
// 	t_env	*content;

// 	i = -1;
// 	result = NULL;
// 	while (envp[++i])
// 	{
// 		line = ft_split(envp[i], '=');
// 		content = (t_env *)malloc(sizeof(t_env));
// 		if (!content)
// 			exit(1);
// 		content->key = line[0];
// 		content->value = line[1];
// 		free(line);
// 		new = ft_lstnew(content);
// 		if (new)
// 			ft_lstadd_back(&result, new);
// 		else
// 			ft_error("Malloc error while generate envlist\n");
// 	}
// 	return (result);
// }

char	**get_env(char **envp)
{
	int		list_size;
	int		i;
	char	**res;

	list_size = 0;
	if (!envp || !(*envp))
		return (NULL);
	while (envp[list_size])
		list_size++;
	i = 0;
	res = (char **)malloc(sizeof(char *) * list_size);
	while (i < list_size)
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
				//printf("value : %s\n", res);
				return (res);
			}
		}
		i++;
	}
	return (NULL);
}

// char	*match_env(char *keystr, t_list *data)//
// {
// 	int		target_l;
// 	int		key_l;
// 	char	*res;

// 	target_l = ft_strlen(keystr);
// 	res = NULL;
// 	while (data)
// 	{
// 		if (ft_strncmp(keystr, ((t_env *)data->content)->key, target_l) == 0)
// 		{
// 			key_l = ft_strlen(((t_env *)data->content)->key);
// 			if (target_l == key_l)
// 			{
// 				res = ((t_env *)data->content)->value;
// 				return (res);
// 			}
// 		}
// 		data = data->next;
// 	}
// 	return (NULL);
// }

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
