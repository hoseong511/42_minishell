/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:09:37 by namkim            #+#    #+#             */
/*   Updated: 2022/08/22 17:36:22 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

//PATH 구조체 필요?
/* 실행 */
/*
	0. implemented 된 명령어인가? -> 해당 함수 호출
	1. PATH -> value호출 -> : 기준으로 split -> 경로를 돌면서 명령어가 존재하는지 점검 -> 존재 시 실행경로 확보
	2. 실행경로 확보시 -> execve로 실행
	3. 실행 성공 ->
		3-2. 실행 실패 ->
	..4. 다음 명령 실행
		0-3 실행
	5. 사용된 모든 구조체 free (token, cmd, path(?))
	6. 다시 prompt 띄우기
*/
char	**get_path(char **envlist)
{
	char	**res;
	char	*path_value;

	path_value = match_env("PATH", envlist);
	res = ft_split(path_value, ':');
	if (path_value)
		free(path_value);
	return (res);
}

char	*get_exe_format(char *path, char *cmd)
{
	char	*temp;
	char	*res;

	res = NULL;
	if (!path && !cmd)
		return (NULL);
	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, cmd);
	free (temp);
	return (res);
}

static int	is_valid_exe_file(char *addr)
{
	struct stat	sb;
	int			sign;

	if (!addr)
		return (0);
	sign = stat(addr, &sb);
	if (sign == 0)
	{
		if ((sb.st_mode & S_IXUSR) != 0)
			return (TRUE);
		else
			return (-1);
	}
	return (-2);
}

//get_filepath로 이름 바꾸기
char	*get_exe_file(char	**envp, char *cmd)
{
	char	*addr;
	int		i;
	int		sign;
	char	**path;

	i = 0;
	addr = NULL;
	path = get_path(envp);
	while (path && path[i])
	{
		addr = get_exe_format(path[i], cmd);
		sign = is_valid_exe_file(addr);
		if (sign == TRUE)
			return (addr);
		free(addr);
		addr = NULL;
		i++;
	}
	if (sign == -1)
		ft_error3(cmd, ": Permission Denied\n", 126);
	if (sign == -2)
		ft_error3(cmd, ": command not found\n", 127);
	addr = cmd;
	return (addr);
}
