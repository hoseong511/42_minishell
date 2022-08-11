/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:20:24 by namkim            #+#    #+#             */
/*   Updated: 2022/08/11 11:33:12 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

void	is_env_exist(void **target, t_list *data)
{
	char	*str;
	char	*keystr;
	int		i;
	int		j;

	str = *((char **)target);
	i = 0;
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
				*target = replace_env(str, keystr, data);
				free(keystr);
				free(str);
				str = *target;
				i = 0;
			}
		}
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
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
			exit(1);
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

static char	*find_env(const char *str, const char *keystr, size_t len)
{
	size_t	i;

	if (*keystr == '\0')
		return ((char *)str);
	i = ft_strlen(keystr);
	while (*str && len-- >= i)
	{
		if (*str == '\'')
		{
			len--;
			str++;
			while (*(str) != '\'')
			{
				str++;
				len--;
			}
			str++;
			len--;
		}
		if (ft_strncmp(str, keystr, i) == 0)
			return ((char *)str);
		str++;
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
	var = find_env(str, keystr, ft_strlen(str));
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
