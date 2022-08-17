/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:46:57 by namkim            #+#    #+#             */
/*   Updated: 2022/08/17 19:53:26 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	get_env_len(char *target)
{
	int	i;

	i = 0;
	while (is_valid_env_name(target[i], i) == TRUE)
		i++;
	return (i);
}

void	replace_env(char **target, int start, int keysize, char **envp)
{
	char	*str;
	char	*keystr;

	str = *target;
	keystr = ft_strndup(str + start, keysize);
	if (!keystr)
		ft_error("Malloc error\n");
	*target = replace_key_to_value(str, start, keystr, envp);
	free(str);
	free(keystr);
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
