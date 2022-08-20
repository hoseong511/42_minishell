/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 22:00:32 by namkim            #+#    #+#             */
/*   Updated: 2022/08/20 21:13:45 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

extern int	g_status;

void	do_expansion(char **target, char **envp, char sign)
{
	int		i;
	int		len;
	int		envs;

	envs = count_env((*target), sign);
	i = -1;
	while ((*target)[++i] && envs)
	{
		if ((*target)[i] == '$')
		{
			++i;
			if ((*target)[i] == '?')
				envp = NULL;
			len = get_env_len((*target) + i);
			if (len != 0)
			{
				replace_env(target, i, len, envp);
				i = -1;
				envs--;
			}
		}
		else if (sign != '\"' && (*target)[i] == '\'')
			i = get_quote_end_idx(*target, i);
	}
}

void	do_replace_in_token(t_cmd *node, char **envp)
{
	char	*target;
	int		j;
	t_list	*cmp;

	target = (char *)node->str;
	cmp = NULL;
	j = 0;
	while (*(target + j))
	{
		if (*(target + j) == '\'' || *(target + j) == '\"')
		{
			if (j == 0)
			{
				j = get_quote_end_idx(target, target - (char *)node->str);
				make_component(&cmp, target, (j - (target - (char *)node->str) + 1), envp);
				target = target + j + 1;
			}
			else
			{
				make_component(&cmp, target, j, envp);
				target += j;
			}
			j = 0;
		}
		else
			j++;
	}
	if (*(target + j) == '\0' && j != 0)
		make_component(&cmp, target, j, envp);
	node->str = join_components(cmp, target);
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
