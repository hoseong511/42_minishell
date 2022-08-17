/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 22:00:32 by namkim            #+#    #+#             */
/*   Updated: 2022/08/17 20:27:47 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

//이 안에 있는 모든 환경변수 변경
//start end로 안 되면 환경변수의 개수 세기?
void	do_expansion(char **target, char **envp, char sign)
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

void	do_replace_in_token(t_cmd *node, char **envp)
{
	char	*target;
	int		i;
	int		j;
	t_list	*component;

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
				process_quote(ft_lstlast(component), envp, target[i]);//
				i = j + 1;
			}
			else
			{
				make_component(&component, target + i, j);
				process_non_quote(ft_lstlast(component), envp);//
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
		process_non_quote(ft_lstlast(component), envp);//
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
