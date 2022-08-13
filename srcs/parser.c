/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:53:51 by namkim            #+#    #+#             */
/*   Updated: 2022/08/13 15:46:55 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

//lst 완전히 새로 생길때?
//ft_strdup으로 만들어야하는거 아닌지? token들 free? or cmd 끝나고 다 같이 free?
void	add_cmd(t_list **lst, char *str, t_type type)
{
	t_cmd	*cmd;
	t_list	*new;

	if (!lst)
		return ;
	cmd = malloc(sizeof(cmd));
	if (!cmd)
		ft_error("Malloc Error while Parsing\n");
	cmd->str = str;
	cmd->type = type;
	new = ft_lstnew(cmd);
	if (!new)
		ft_error("Malloc Error while Parsing\n");
	ft_lstadd_back(lst, new);
}

t_type	get_cmd_type(char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
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
		type = get_cmd_type((char *)tnode->content);
		add_cmd(&res, (char *)tnode->content, type);
		if (type > PIPE && type < R_ARG)
		{
			tnode = tnode->next;
			type = R_ARG;
			add_cmd(&res, (char *)tnode->content, type);
		}
		else if (type == PIPE)
			data->pip_cnt++;
		tnode = tnode->next;
	}
	return (res);
}
