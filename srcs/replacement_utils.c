/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacement_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:51:40 by namkim            #+#    #+#             */
/*   Updated: 2022/08/20 18:35:08 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

//환경변수 expansion
//single quote / doublequote 처리
//re_tokenize
void	process_is_quote(t_list *component, char **envp, char quote)
{
	char	*str;

	if (!component)
		return ;
	str = (char *)component->content;
	if (quote == '\"' || quote == '\'')
	{
		if (quote == '\"')
			do_expansion(&str, envp, quote);
		remove_quote(&str, 0, ft_strlen(str) - 1);
	}
	else
		do_expansion(&str, envp, 'a');
	component->content = str;
}

void	make_component(t_list **lst, char *src, int size, char **envp)
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
	process_is_quote(new, envp, *str);
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

char	*join_components(t_list *component, char *target)
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
	free(target);
	return (res);
}
