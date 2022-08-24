/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:52:14 by hossong           #+#    #+#             */
/*   Updated: 2022/08/24 18:02:50 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	check_pipe_syntax(t_data *data)
{
	t_list	*tnode;
	t_type	tnext;

	tnode = data->tokenlist;
	if (((t_cmd *)tnode->content)->type == PIPE \
			&& !ft_syntax_error(((t_cmd *)tnode->content)->type, NULL))
		return (FALSE);
	data->cmd_cnt++;
	while (tnode)
	{
		if (((t_cmd *)tnode->content)->type == PIPE)
		{
			if (!tnode->next \
					&& !ft_syntax_error(((t_cmd *)tnode->content)->type, NULL))
				return (FALSE);
			tnext = ((t_cmd *)tnode->next->content)->type;
			if (tnext != PIPE && tnext != NONE)
				data->cmd_cnt++;
			else if (!ft_syntax_error(((t_cmd *)tnode->content)->type, NULL))
				return (FALSE);
		}
		tnode = tnode->next;
	}
	return (TRUE);
}

int	check_redirection_syntax(t_data *data)
{
	t_list	*tnode;
	t_type	type;
	int		sign;

	sign = TRUE;
	tnode = data->tokenlist;
	while (tnode)
	{
		type = ((t_cmd *)tnode->content)->type;
		if (type > PIPE && type < R_ARG)
		{
			if (!tnode->next)
				sign = ft_syntax_error(type, NULL);
			else if (((t_cmd *)tnode->next->content)->type == ARGS)
			{
				((t_cmd *)tnode->next->content)->type = R_ARG;
				tnode = tnode->next;
			}
			else
				sign = ft_syntax_error(type, ((t_cmd *)tnode->content)->str);
		}
		tnode = tnode->next;
	}
	return (sign);
}
