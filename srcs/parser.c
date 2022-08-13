/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:53:51 by namkim            #+#    #+#             */
/*   Updated: 2022/08/13 21:10:40 by namkim           ###   ########.fr       */
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


void	add_type(t_list *lst, t_type type)
{
	t_list	*node;

	if (!lst)
		return ;
	node = lst;
	while (node)
	{
		((t_cmd *)node->content)->type = type;
		node = node->next;
	}
}

t_type	get_cmd_type(char *str)
{
	if (ft_strncmp(str, "", 1) == 0)	//통하는지 check & NONE 과 NULL 분리할지?
		return (NONE);
	else if (ft_strncmp(str, "|", 2) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "<", 2) == 0)
		return (R_IN);
	else if (ft_strncmp(str, ">", 2) == 0)
		return (R_OUT);
	else if (ft_strncmp(str, "<<", 3) == 0)
		return (R_HEREDOC);
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (R_APPD);
	else
		return (ARGS);
}

//or lexer
//syntax_check
/* 검사해야 하는 부분
1. Redirection Args 있는지
2. Pipe가 제일 첫 인자로 들어오는지(Error)
3. Pipe가 연속되는지(pip 뒤에 하나 이상의 arg가 있는지 (redirection만으로 구성 가능?)) */
t_list	*lexer(t_data *data)
{
	t_list	*res;
	t_list	*tnode;
	t_type	type;

	res = NULL;
	if (!data || !data->tokenlist)
		return (NULL);
	tnode = data->tokenlist;
	while (tnode)
	{
		type = get_cmd_type((char *)((t_cmd *)tnode->content)->str);
		add_type(tnode, type);
		if (type == PIPE)	//
			data->pip_cnt++;
		tnode = tnode->next;
	}
	print_t_cmds(data->tokenlist);
	tnode = data->tokenlist;
	while (tnode)	//여기서 문법 검사가 필요하다.
	{
		type = ((t_cmd *)tnode->content)->type;
		if (type > PIPE && type < R_ARG)
		{
			if (((t_cmd *)tnode->next->content)->type == ARGS)
				((t_cmd *)tnode->next->content)->type = R_ARG;
			else
				ft_error("Syntax Error : Redirection has no args\n");
		}
		tnode = tnode->next;
	}
	print_t_cmds(data->tokenlist);
	return (res);
}
