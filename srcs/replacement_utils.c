/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacement_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:51:40 by namkim            #+#    #+#             */
/*   Updated: 2022/08/21 20:14:54 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	make_component(t_list **lst, char *src, int size)
{
	char	*str;
	t_list	*new;

	if (!lst)
		return ;
	str = ft_strndup(src, size);
	if (!str)
		return ;
	new = ft_lstnew(str);
	if (!new)
		ft_error("ERROR: Malloc Error while replacement\n");
	ft_lstadd_back(lst, new);
}

void	delete_component(t_list *cnode)
{
	void	*content;

	if (!cnode)
		return ;
	content = cnode->content;
	free(cnode);
	cnode = NULL;
	if (!content)
		return ;
	free(content);
	content = NULL;
}

char	*join_components(t_list *component)
{
	t_list	*node;
	t_list	*ltemp;
	char	*temp;
	char	*res;

	node = component;
	res = NULL;
	while (node)
	{
		temp = res;
		res = ft_strjoin(res, (char *)node->content);
		ltemp = node;
		node = node->next;
		delete_component(ltemp);
		free(temp);
	}
	return (res);
}

t_list	*split_words(char *target, int i, int j)
{
	t_list	*component;

	component = NULL;
	while (target[i + j])
	{
		if (target[i + j] == '\'' || target[i + j] == '\"')
		{
			if (j == 0)
			{
				j = get_quote_end_idx(target, i);
				make_component(&component, target + i, (j - i + 1));
				i++;
			}
			else
				make_component(&component, target + i, j);
			i += j;
			j = 0;
		}
		else
			j++;
	}
	if (target[i + j] == '\0' && j != 0)
		make_component(&component, target + i, j);
	return (component);
}
