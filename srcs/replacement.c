/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 22:00:32 by namkim            #+#    #+#             */
/*   Updated: 2022/08/15 21:09:06 by hossong          ###   ########.fr       */
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

void	replace_env(char **target, int start, int keysize, t_list *envp)
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

//이 안에 있는 모든 환경변수 변경
//start end로 안 되면 환경변수의 개수 세기?
void	do_expansion(char **target, t_list *envp, char sign)
{
	char	*str;
	int		i;
	int		len;
	int		envs;

	str = (*target);
	envs = count_env(str, sign);
	i = 0;
	while (str[i] && envs)
	{
		if (str[i] == '$')
		{
			++i;
			len = get_env_len(str + i);
			if (len != 0)
			{
				replace_env(target, i, len, envp);
				i = 0;
				str = (*target);
				envs--;
			}
		}
		else if (sign != '\"' && str[i] == '\'')
			i = get_quote_end_idx(*target, i);
		i++;
	}
}

void	do_replace_in_token(t_cmd *node, t_list *envp)
{
	char	*target;
	int		i;
	int		j;
	t_list	*component;
	t_list	*this;

	target = (char *)node->str;
	i = 0;
	j = 0;
	component = NULL;
	while (target[i + j])
	{
		if (target[i + j] == '\'' || target[i + j] == '\"')
		{
			if (j == 0)
			{
				j = get_quote_end_idx(target, i);
				make_component(&component, target + i, (j - i + 1));
				process_quote(ft_lstlast(component), envp, target[i]);
				i = j + 1;
			}
			else
			{
				make_component(&component, target + i, j);
				process_non_quote(ft_lstlast(component), envp);
				i += j;
			}
			j = 0;
		}
		else
			j++;
	}
	if (target[i + j] == '\0' && j != 0)
	{
		make_component(&component, target + i, j);
		this = ft_lstlast(component);
		process_non_quote(ft_lstlast(component), envp);
	}
	if (component)
		node->str = join_components(component);
	free(target);
}

void	remove_quote(char **target, int startidx, int endidx)
{
	char	*str;
	char	*dst;

	str = *target;
	dst = str + (startidx);
	str = ft_memmove(dst, dst + 1, ft_strlen(dst + 1) - 1);
	str[endidx - 1] = '\0';
}
