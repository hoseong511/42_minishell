/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:46:57 by namkim            #+#    #+#             */
/*   Updated: 2022/08/13 14:58:08 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_data	*init_shell(char **envp)
{
	t_data	*res;

	res = malloc(sizeof(t_data));
	if (!res)
		ft_error("Malloc Error While Initialize\n");
	res->envlist = get_env(envp);
	res->tokenlist = NULL;
	res->cmdlist = NULL;
	res->pip_cnt = 0;
	return (res);
}
