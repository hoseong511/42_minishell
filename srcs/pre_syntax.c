/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:52:14 by hossong           #+#    #+#             */
/*   Updated: 2022/08/22 21:16:43 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	pop_quote(t_list **quote)
{
	t_list	*temp;

	temp = *quote;
	*quote = (*quote)->next;
	free(temp);
}

int	check_quote(char *str)
{
	int		i;
	t_list	*quote;

	i = -1;
	quote = NULL;
	if (!str)
		return (FALSE);
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!quote)
				quote = ft_lstnew(&str[i]);
			else if (quote && (*(char *)(quote->content)) != str[i])
				ft_lstadd_front(&quote, ft_lstnew(&str[i]));
			else
				pop_quote(&quote);
		}
	}
	if (quote)
	{
		free(quote);
		return (FALSE);
	}
	return (TRUE);
}

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
