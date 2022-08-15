/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:20:24 by namkim            #+#    #+#             */
/*   Updated: 2022/08/15 17:50:25 by namkim           ###   ########.fr       */
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

t_list	*get_env(char **envp)
{
	int		i;
	char	**line;
	t_list	*result;
	t_list	*new;
	t_env	*content;

	i = -1;
	result = NULL;
	while (envp[++i])
	{
		line = ft_split(envp[i], '=');
		content = (t_env *)malloc(sizeof(t_env));
		if (!content)
			exit(1);
		content->key = line[0];
		content->value = line[1];
		free(line);
		new = ft_lstnew(content);
		if (new)
			ft_lstadd_back(&result, new);
		else
			ft_error("Malloc error while generate envlist\n");
	}
	return (result);
}

char	*match_env(char *keystr, t_list *data)
{
	int		target_l;
	int		key_l;
	char	*res;

	target_l = ft_strlen(keystr);
	res = NULL;
	while (data)
	{
		if (ft_strncmp(keystr, ((t_env *)data->content)->key, target_l) == 0)
		{
			key_l = ft_strlen(((t_env *)data->content)->key);
			if (target_l == key_l)
			{
				res = ((t_env *)data->content)->value;
				return (res);
			}
		}
		data = data->next;
	}
	return (NULL);
}

char	*replace_key_to_value(char *str, int start, char *keystr, t_list *data)
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
		var = match_env(keystr, data);
		if (var)
		{
			res = ft_strjoin(prev, var);
			free (prev);
			prev = res;
			res = ft_strjoin(prev, next);
		}
		else
			res = ft_strjoin(prev, next);
		free(prev);
		free(next);
	}
	return (res);
}
