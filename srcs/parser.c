/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:53:51 by namkim            #+#    #+#             */
/*   Updated: 2022/08/17 20:26:28 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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

void	add_cmd2(t_list **lst, char **str, t_type type)
{
	t_cmd2	*cmd2;
	t_list	*new;

	cmd2 = (t_cmd2 *)malloc(sizeof(t_cmd2));
	if (!cmd2)
		ft_error("ERROR: malloc error\n");
	cmd2->str = str;
	cmd2->type = type;
	new = ft_lstnew(cmd2);
	if (!new)
		ft_error("ERROR: malloc error\n");
	ft_lstadd_back(lst, new);
}

t_type	get_cmd_type(char *str)
{
	if (ft_strncmp(str, "", 1) == 0)
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

static void	put_type(t_data *data)
{
	t_type	type;
	t_list	*tnode;

	tnode = data->tokenlist;
	while (tnode)
	{
		type = get_cmd_type((char *)((t_cmd *)tnode->content)->str);
		add_type(tnode, type);
		tnode = tnode->next;
	}
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

	res = NULL;
	if (!data || !data->tokenlist)
		return (NULL);
	put_type(data);
	check_pipe_syntax(data);
	check_redirection_syntax(data);
	res = data->tokenlist;
	while (res)
	{
		do_replace_in_token(res->content, data->envlist);
		res = res->next;
	}
	print_t_cmds(data->tokenlist);
	res = data->tokenlist;
	// printf("how many commands: %d\n", data->cmd_cnt);
	return (res);
}
