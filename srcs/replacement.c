/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 22:00:32 by namkim            #+#    #+#             */
/*   Updated: 2022/08/21 12:25:42 by namkim           ###   ########.fr       */
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
