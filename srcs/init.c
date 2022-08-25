/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:46:57 by namkim            #+#    #+#             */
/*   Updated: 2022/08/25 13:29:42 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	raise_shlvl(t_data *data)
{
	char	**envp;
	char	*shlvl;
	char	*temp;
	int		level;

	envp = data->envlist;
	if (!envp || !(*envp))
		return ;
	shlvl = match_env("SHLVL", envp);
	if (!shlvl)
		insert_env("SHLVL=1", data);
	else
	{
		level = ft_atoi(shlvl);
		level++;
		free(shlvl);
		temp = ft_itoa(level);
		shlvl = ft_strjoin("SHLVL=", temp);
		insert_env(shlvl, data);
		free(temp);
		free(shlvl);
	}
}

t_data	*init_data(char **envp)
{
	t_data	*res;

	res = malloc(sizeof(t_data));
	if (!res)
		ft_error("Malloc Error While Initialize\n");
	res->envlist = get_env(envp, res);
	raise_shlvl(res);
	res->envlist_cnt = res->envlist_size;
	res->tokenlist = NULL;
	res->cmdlist = NULL;
	res->cmd_cnt = 0;
	res->heredoc = NULL;
	res->fd_stdin = dup(0);
	if (res->fd_stdin == -1)
		ft_perror("dup", errno);
	res->fd_stdout = dup(1);
	if (res->fd_stdout == -1)
		ft_perror("dup", errno);
	g_status = 0;
	printf("==minishell==\n");
	return (res);
}

void	re_initialize(t_data *data)
{
	free_process(data);
	free_cmdlist(data->cmdlist);
	data->cmdlist = NULL;
	data->tokenlist = NULL;
	data->cmd_cnt = 0;
	data->info = NULL;
	data->heredoc = NULL;
	ft_dup2(data->fd_stdin, 0);
	ft_dup2(data->fd_stdout, 1);
}

void	load_data(t_data *data, char *str)
{
	data->tokenlist = tokenizer(str);
	if (!data->tokenlist)
		return ;
	data->tokenlist = lexer(data);
	if (data->tokenlist == NULL)
		return ;
	data->cmdlist = relocate(&data->tokenlist);
	data->cmdlist = bind(data->cmdlist);
}
