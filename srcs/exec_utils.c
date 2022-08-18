/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:09:37 by namkim            #+#    #+#             */
/*   Updated: 2022/08/18 16:30:01 by namkim           ###   ########.fr       */
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
char	**get_path(t_data *data)
{
	char	**res;
	char	*path_value;

	path_value = match_env("PATH", data->envlist);
	res = ft_split(path_value, ':');
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

//get_filepath로 이름 바꾸기
char	*get_exe_file(char	**path, char *cmd, t_data *data)
{
	char		*res;
	char		*addr;
	int			i;
	struct stat	sb;
	int			sign;

	i = 0;
	res = NULL;
	while (path[i])
	{
		addr = get_exe_format(path[i], cmd);
		sign = stat(addr, &sb);
		if (sign == 0)
		{
			if ((sb.st_mode & S_IXUSR) != 0)
			{
				res = addr;
				return (res);
			}
			else
				data->status = -5;
			return (res);
		}
		free(addr);
		i++;
	}
	return (res);
}
