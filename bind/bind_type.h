/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_type.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:54:56 by hossong           #+#    #+#             */
/*   Updated: 2022/08/12 19:46:08 by hossong          ###   ########.fr       */
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
							//이후 exit status등 필요한 데이터 추가
}	t_data;

void	ft_error(char *err_msg);
void	dummy_data(t_data *data);
void	relocation_type(t_list *cmdlist);

#endif
