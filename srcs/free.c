/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:45:35 by namkim            #+#    #+#             */
/*   Updated: 2022/08/22 15:01:59 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

/* free목록
1. envlist
2. tokenlist
3. cmdlist
4. t_proc *info	// free필요? pipe?
*/

void	free_envlist(t_data *data)
{
	char	**envlist;
	int		i;

	envlist = data->envlist;
	i = -1;
	if (!envlist)
		return ;
	while (envlist[++i])
		free(envlist[i]);
	free(envlist);
	data->envlist_cnt = 0;
	data->envlist_size = 0;
}

static void	free_cmd(void *cmdcontent)
{
	char	*str;

	str = ((t_cmd *)cmdcontent)->str;
	free(str);
	str = NULL;
	free(cmdcontent);	//가능하겠지...?
}

static void	free_cmd2(void *cmd2content)
{
	char	**strs;

	strs = ((t_cmd2 *)cmd2content)->str;
	while (*strs)
	{
		free(*strs);
		*strs = NULL;
		strs++;
	}
	free(cmd2content);
}

void	free_tokenlist(t_list *tokenlist)
{
	t_list	*node;
	char	*str;

	node = tokenlist;
	ft_lstclear(&tokenlist, free_cmd);	//libft 확인할 것
}

void	free_cmdlist(t_list *cmdlist)
{
	t_list	*node;
	char	*str;

	node = cmdlist;
	ft_lstclear(&cmdlist, free_cmd2);
}

//t_proc, 다른 stat들 initialize 필요
