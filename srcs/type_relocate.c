/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_relocate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 20:58:55 by hossong           #+#    #+#             */
/*   Updated: 2022/08/22 21:30:10 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	insert_inout(t_list **des, t_list **in, t_list **out, t_list **tmp)
{
	insert_src(des, out, tmp);
	insert_src(des, in, tmp);
}

static void	append_inout(t_list **tokenlist, t_list **in, t_list **out)
{
	t_type	type;

	type = ((t_cmd *)(*tokenlist)->content)->type;
	if (type == R_IN || type == R_HEREDOC)
		append_ab(in, pop(tokenlist), pop(tokenlist));
	else if (type == R_OUT || type == R_APPD)
		append_ab(out, pop(tokenlist), pop(tokenlist));
}

t_list	*relocate(t_list **tokenlist)
{
	t_list	*des;
	t_list	*src_in;
	t_list	*src_out;
	t_list	*tmp;

	des = NULL;
	tmp = NULL;
	src_in = NULL;
	src_out = NULL;
	while ((*tokenlist))
	{
		if (((t_cmd *)(*tokenlist)->content)->type > PIPE)
			append_inout(tokenlist, &src_in, &src_out);
		else if (((t_cmd *)(*tokenlist)->content)->type == PIPE)
		{
			insert_inout(&des, &src_in, &src_out, &tmp);
			tmp = pop(tokenlist);
			ft_lstadd_back(&des, tmp);
		}
		else if (((t_cmd *)(*tokenlist)->content)->type == ARGS)
			ft_lstadd_back(&des, pop(tokenlist));
		if (!(*tokenlist))
			insert_inout(&des, &src_in, &src_out, &tmp);
	}
	return (des);
}
