/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:42:28 by hossong           #+#    #+#             */
/*   Updated: 2022/08/14 17:07:32 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	free_cmdlist(t_data *data)
{
	t_list	*tmp;
	int		i;

	while (data->cmdlist)
	{
		tmp = data->cmdlist->next;
		i = 0;
		while (((t_cmd2 *)data->cmdlist->content)->str[i])
		{
			free(((t_cmd2 *)data->cmdlist->content)->str[i]);
			i++;
		}
		free(((t_cmd2 *)data->cmdlist->content)->str);
		free(data->cmdlist->content);
		free(data->cmdlist);
		data->cmdlist = tmp;
	}
}

void	free_tokenlist(t_data *data)
{
	t_list	*tmp;

	while (data->tokenlist)
	{
		tmp = data->tokenlist->next;
		free(data->tokenlist);
		data->tokenlist = tmp;
	}
}

void	free_data(t_data *data)
{
	t_list	*tmp;

	while (data->envlist)
	{
		tmp = data->envlist->next;
		free(((t_env *)data->envlist->content)->key);
		free(((t_env *)data->envlist->content)->value);
		free(data->envlist->content);
		free(data->envlist);
		data->envlist = tmp;
	}
	free(data);
}

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
		free(str);
		if (data->status == FALSE)
			continue ;
		if (data->cmdlist)
		{
			if (ft_strncmp(((t_cmd2 *)data->cmdlist->content)->str[0], "exit", 5) == 0)
			{
				free_tokenlist(data);
				free_cmdlist(data);
				break ;
			}
		}
		free_tokenlist(data);
		free_cmdlist(data);
		system("leaks minishell");
	}
	free_data(data);
	system("leaks minishell");
	return (0);
}
