/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 22:00:32 by namkim            #+#    #+#             */
/*   Updated: 2022/08/23 16:09:34 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	get_quote_end_idx(char *str, int i)
{
	int		j;
	char	q;

	q = str[i];
	j = 1;
	while (str[i + j] && str[i + j] != q)
		j++;
	if (str[i + j] != q)
		printf("unclosed quotes\n");
	return (i + j);
}

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
	char	first;

	target = (char *)cmdnode->str;
	comp = split_words(target, 0, 0);
	node = comp;
	while (node)
	{
		first = ((char *)node->content)[0];
		do_expansion((char **)&(node->content), envp, first);
		if (first == '\"' || first == '\'')
			remove_quote((char **)&(node->content), 0, \
							ft_strlen((char *)node->content) - 1);
		node = node->next;
	}
	cmdnode->str = join_components(comp);
	free(target);
}
