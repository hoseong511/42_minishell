/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 21:35:13 by namkim            #+#    #+#             */
/*   Updated: 2022/08/15 20:57:18 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	print_t_cmds(t_list *tokenlist)
{
	t_list	*node;
	int		type;
	char	*str;
	int		idx;

	node = tokenlist;
	if (!node)
		printf("No tokens\n");
	idx = 0;
	while (node)
	{
		type = ((t_cmd *)node->content)->type;
		str = ((t_cmd *)node->content)->str;
		printf("[%d] <%d> %s\n", idx, type, str);
		node = node->next;
		idx++;
	}
}

void	print_t_cmds2(t_list *tokenlist)
{
	t_list	*node;
	int		type;
	char	**str;
	int		idx;

	node = tokenlist;
	if (!node)
		printf("No tokens\n");
	idx = 0;
	while (node)
	{
		type = ((t_cmd2 *)node->content)->type;
		str = ((t_cmd2 *)node->content)->str;
		printf("[%d] <%d> ", idx, type);
		while (*str)
		{
			printf("%s", *str);
			str++;
		}
		printf("\n");
		node = node->next;
		idx++;
	}
}
