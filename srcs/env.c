/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:20:24 by namkim            #+#    #+#             */
/*   Updated: 2022/08/13 14:59:09 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	search_env_var(t_list *data, char *var)
{
	while (data)
	{
		if (!ft_strncmp(var, ((t_env *)data->content)->key, ft_strlen(var)))
		{
			if (ft_strlen(var) == ft_strlen(((t_env *)data->content)->key))
			{
				free(var);
				var = ((t_env *)data->content)->value;
				break ;
			}
			else
			{
				free(var);
				var = NULL;
			}
		}
		data = data->next;
	}
}

void	replace_env(char **str, t_list *data)
{
	int		i;
	char	*var;
	char	*prev;
	char	*next;
	int		d;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '$')
		{
			i++;
			if ((*str)[i] == '\'')
			{
				d = ft_strchr(*str + i + 1, '\'') - (*str + i);
				i += d;
				printf("str[i]: %c", (*str)[i]);
			}
			else
			{
				d = ft_strchr(*str + i, ' ') - (*str + i);
				prev = ft_strndup(*str, i - 1);
				var = ft_strndup(*str + i, d);
				next = ft_strdup(*str + i + d + 1);
				search_env_var(data, var);
			}
		}
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
		new = ft_lstnew(content);
		if (new)
			ft_lstadd_back(&result, new);
		else
			exit(1);
	}
	return (result);
}
