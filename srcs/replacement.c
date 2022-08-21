/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 22:00:32 by namkim            #+#    #+#             */
/*   Updated: 2022/08/21 20:14:47 by hossong          ###   ########.fr       */
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

void	remove_quote(char **target, int startidx, int endidx)
{
	char	*str;
	char	*dst;

	str = *target;
	dst = str + (startidx);
	str = ft_memmove(dst, dst + 1, ft_strlen(dst + 1) - 1);
	str[endidx - 1] = '\0';
}

void	do_replace_in_token(t_cmd *cmdnode, char **envp)
{
	t_list	*comp;
	t_list	*node;
	char	*target;

	target = (char *)cmdnode->str;
	comp = split_words(target, 0, 0);
	node = comp;
	while (node)
	{
		do_expansion((char **)&(node->content), envp, (char)(node->content));
		node = node->next;
	}
	cmdnode->str = join_components(comp);
	free(target);
}
