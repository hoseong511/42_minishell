/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:46:57 by namkim            #+#    #+#             */
/*   Updated: 2022/08/14 21:57:13 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

//환경변수 expansion
//single quote / doublequote 처리
//re_tokenize
void	process_quote(t_list *component, t_list *envp, char quote)
{
	char	*str;

	if (!component)
		return ;
	str = (char *)component->content;
	if (quote == '\"')
		do_expansion(&str, envp, quote);
	remove_quote(&str, 0, ft_strlen(str) - 1);
}

void	process_non_quote(t_list *component, t_list *envp)
{
	char	*str;

	if (!component)
		return ;
	str = (char *)component->content;
	do_expansion(&str, envp, 'a');
}

void	make_component(t_list **lst, char *src, int size)
{
	char	*str;
	t_list	*new;

	if (!lst)
		return ;
	str = ft_strndup(src, size);
	printf("token cmp: %s\n", str);
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

t_data	*init_data(char **envp)
{
	t_data	*res;

	res = malloc(sizeof(t_data));
	if (!res)
		ft_error("Malloc Error While Initialize\n");
	res->envlist = get_env(envp);
	res->tokenlist = NULL;
	res->cmdlist = NULL;
	res->pip_cnt = 0;
	res->status = TRUE;
	return (res);
}

void	load_data(t_data *data, char *str)
{
	t_list	*token;
//	t_list	*node;

	data->status = check_quote(str);
	if (data->status == FALSE)
		return ;
	data->tokenlist = tokenizer(str);
	token = data->tokenlist;
	// while (token)
	// {
	// 	str = (char *)token->content;
	// 	 replacement(&str, data->envlist);
	// 	printf("str: %s\n", str);
	// 	token = token->next;
	// }
//	data->cmdlist = lexer(data);
//	print_t_cmds(data->tokenlist);
	lexer(data);
	// data->cmdlist = relocate_type(data->cmdlist);
	// t_list	*reloc = data->cmdlist;
	// while (reloc)
	// {
	// 	printf("%s\n", ((t_cmd *)(reloc->content))->str);
	// 	reloc = reloc->next;
	// }
}
