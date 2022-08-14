/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_excution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:27:01 by hossong           #+#    #+#             */
/*   Updated: 2022/08/14 18:02:02 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	execute_cmd(t_data *data)
{
	char	**cmd;

	if (data->cmdlist)
	{
		cmd = ((t_cmd2 *)data->cmdlist->content)->str;
		if (ft_strncmp(cmd[0], "exit", 5) == 0)
		{
			free_tokenlist(data);
			free_cmdlist(data);
			exit(0);
		}
		else if (ft_strncmp(cmd[0], "echo", 5) == 0)
			;
		else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
			;
		else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
			;
		else if (ft_strncmp(cmd[0], "export", 7) == 0)
			printf("export\n");
	}	
}
