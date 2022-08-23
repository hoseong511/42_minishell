/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:46:57 by namkim            #+#    #+#             */
/*   Updated: 2022/08/22 21:04:50 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	get_env_len(char *target)
{
	int	i;

	i = 0;
	if (target[0] == '?')
		return (1);
	while (is_valid_env_name(target[i], i) == TRUE)
		i++;
	return (i);
}

void	replace_env(char **target, int start, int keysize, char **envp)
{
	char	*str;
	char	*keystr;

	str = *target;
	if (envp == NULL)
		*target = replace_key_to_value(str, start, "?", NULL);
	else
	{
		keystr = ft_strndup(str + start, keysize);
		if (!keystr)
			ft_error("Malloc error\n");
		*target = replace_key_to_value(str, start, keystr, envp);
		free(keystr);
	}
	free(str);
}

static void	free_double_string(char *str1, char *str2)
{
	if (str1)
		free (str1);
	if (str2)
		free (str2);
}

static char	*join_three_string(char **prev, char **var, char **next)
{
	char	*res;

	res = ft_strjoin(*prev, *var);
	free_double_string(*prev, *var);
	*prev = res;
	res = ft_strjoin(*prev, *next);
	return (res);
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
			res = join_three_string(&prev, &var, &next);
		else
			res = ft_strjoin(prev, next);
		free_double_string(prev, next);
	}
	return (res);
}
