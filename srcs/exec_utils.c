/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:09:37 by namkim            #+#    #+#             */
/*   Updated: 2022/08/16 21:40:31 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

//PATH 구조체 필요?
/* 실행 */
/*
	0. implemented 된 명령어인가? -> 해당 함수 호출
	1. PATH -> value호출 -> : 기준으로 split -> 경로를 돌면서 명령어가 존재하는지 점검 -> 존재 시 실행경로 확보
	2. 실행경로 확보시 -> execve로 실행
*/

char	**get_path(t_data *data)
{
	char	**res;
	char	*path_value;

	path_value = match_env("PATH", data);
	res = ft_split(path_value, ':');
	return (res);
}

char	*get_exe_file(char	**path, char *cmd)
{
	char		*res;
	char		*addr;
	int			i;
	struct stat	sb;
	int			sign;

	i = -1;
	res = NULL;
	while (path[i])
	{
		addr = ft_strjoin(path[i], cmd);
		sign = stat(addr, &sb);	//호출 성공시 0, 실패시 -1 & errno set
		if (sign == 0)
		{
			//먼저 권한체크 : 읽기 / 실행일 때 각각 다름....
			//만약 권한이 없다면 : continue;
			//id user로 했을 때 group 권한을 다 줬는데 왜 안 읽히는지...?
							//000중 어느쪽을 기준으로 권한 체크해야하는지?
							//우선은 소유주를 기준으로 체크
			//만약 권한이 있을 때 (실행가능한 상태일 때)
			if ((sb.st_mode & S_IXUSR) != 0)
			{
				res = addr;
				return (res);
			}
		}
		free(addr);
	}
	return (res);
}
