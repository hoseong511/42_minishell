/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_type.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:54:56 by hossong           #+#    #+#             */
/*   Updated: 2022/08/13 01:18:55 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIND_TYPE_H
# define BIND_TYPE_H

# include "libft/libft.h"
# include <stdio.h>

typedef enum e_type
{
	ARGS,
	PIPE,
	R_IN,
	R_OUT,
	R_APPD,
	R_HEREDOC,
	R_ARG
}	t_type;

typedef struct s_cmd
{
	char		*str;
	t_type		type;
}	t_cmd;

typedef struct s_data
{
	t_list		*envlist;
	t_list		*tokenlist;
	t_list		*cmdlist;
	int			pip_cnt;	//or 실행해야하는 process의 수
}	t_data;

void	ft_error(char *err_msg);
void	dummy_data(t_data *data);
t_list	*relocate_type(t_list *cmdlist);
void	insert(t_list *a, t_list *b);
void	push(t_list **list, t_list *node);
t_list	*pop(t_list **list);



#endif
