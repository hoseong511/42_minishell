/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:20:24 by namkim            #+#    #+#             */
/*   Updated: 2022/08/13 15:38:20 by hossong          ###   ########.fr       */
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

void	is_env_exist(t_list *target, t_list *data)
{
	char	*str;
	char	*keystr;
	char	*value;
	int		i;
	int		j;

	str = (char *)target->content;
	i = 0;
	value = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			j = 0;
			while (is_valid_env_name(str[i + j], j) == TRUE)
				j++;
			if (j != 0)
			{
				keystr = ft_strndup(str + i, j);
				if (!keystr)
					ft_error("Malloc error\n");
				target->content = replace_env(str, keystr, data);
				free(keystr);
				free(str);
			}
			str = target->content;
			i = -1;
		}
		i++;
	}

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

char	*replace_env(char *str, char *keystr, t_list *data)
{
	char	*var;
	char	*prev;
	char	*next;
	char	*res;

	res = NULL;
	var = ft_strnstr(str, keystr, ft_strlen(str));
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
