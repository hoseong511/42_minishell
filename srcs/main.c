/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:42:28 by hossong           #+#    #+#             */
/*   Updated: 2022/08/17 18:10:03 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_data	*data;

	(void) argv;
	if (argc != 1)
		ft_error("Too much argument!\n");
	printf("==minishell==\n");
	data = init_data(envp);
	while (1)
	{
		str = readline("mini-0.1$ ");
		load_data(data, str);
		if (data->status == FALSE)
			continue ;
		execution(data);
		// free_cmdlist(data->cmdlist);
		free(str);
	}
	free_data(data);
	return (0);
}
