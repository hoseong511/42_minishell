/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:41:54 by namkim            #+#    #+#             */
/*   Updated: 2022/08/09 14:32:39 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//1. 포함되지 말아야할 문자가 있는지 '\'
//2. 닫히지 않은 quote가 있는지
static void	pop_quote(t_list **quote)
{
	t_list	*temp;

	temp = *quote;
	*quote = (*quote)->next;
	free(temp);
}

t_error	check_quote(char *str)
{
	int		i;
	t_list	*quote;

	i = -1;
	quote = NULL;
	if (ft_strstr(str, INHIBIT))
		return (ERROR);
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!quote)
				quote = ft_lstnew(&str[i]);
			else if (quote && (*(char *)(quote->content)) != str[i]) // void* conversion
				ft_lstadd_front(&quote, ft_lstnew(&str[i]));
			else
				pop_quote(&quote);
		}
	}
	if (quote)
	{
		free(quote);
		return (ERROR);
	}
	return (SUCCESS);
}

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
