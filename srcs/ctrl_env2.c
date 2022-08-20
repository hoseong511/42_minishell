/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:46:57 by namkim            #+#    #+#             */
/*   Updated: 2022/08/20 17:53:23 by hossong          ###   ########.fr       */
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
		free(str);
		free(keystr);
	}
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

void	do_replace(t_list *com, int *i, int *j, char *target)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (target[i + j])
	{
		if (target[i + j] == '\'' || target[i + j] == '\"')
		{
			if (j == 0)
			{
				j = get_quote_end_idx(target, i);
				make_component(&com, target + i, (j - i + 1));
				process_quote(ft_lstlast(com), envp, target[i]);//
				i = j + 1;
			}
			else
			{
				make_component(&com, target + i, j);
				process_non_quote(ft_lstlast(com), envp);//
				i += j;
			}
			j = 0;
		}
		else
			j++;
	}
}
