/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:20:24 by namkim            #+#    #+#             */
/*   Updated: 2022/08/09 17:25:54 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	clear_lst(char **lst, int i)
{
	while (i--)
		free(lst[i]);
	free(lst);
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
