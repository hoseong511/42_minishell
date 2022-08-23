/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:52:14 by hossong           #+#    #+#             */
/*   Updated: 2022/08/23 14:47:19 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	check_pipe_syntax(t_data *data)
{
	t_list	*tnode;
	t_type	tnext;

	tnode = data->tokenlist;
	if (((t_cmd *)tnode->content)->type == PIPE)
		ft_error("Syntax Error : syntax error near unexpected token `|'\n");
	data->cmd_cnt++;
	while (tnode)
	{
		if (((t_cmd *)tnode->content)->type == PIPE)
		{
			if (!tnode->next)
				ft_error("Syntax Error : \
syntax error near unexpected token `|'\n");
			tnext = ((t_cmd *)tnode->next->content)->type;
			if (tnext != PIPE && tnext != NONE)
				data->cmd_cnt++;
			else
				ft_error("Syntax Error : \
syntax error near unexpected token `|'\n");
		}
		tnode = tnode->next;
	}
}

void	check_redirection_syntax(t_data *data)
{
	t_list	*tnode;
	t_type	type;

	tnode = data->tokenlist;
	while (tnode)
	{
		type = ((t_cmd *)tnode->content)->type;
		if (type > PIPE && type < R_ARG)
		{
			if (!tnode->next)
				ft_error("Syntax Error :\
syntax error near unexpected token `newline'\n");
			else if (((t_cmd *)tnode->next->content)->type == ARGS)
				((t_cmd *)tnode->next->content)->type = R_ARG;
			else
				ft_error("Syntax Error : syntax error near unexpected token\n");
			tnode = tnode->next;
		}
		tnode = tnode->next;
	}
}
