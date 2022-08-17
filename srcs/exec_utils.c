/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:09:37 by namkim            #+#    #+#             */
/*   Updated: 2022/08/17 19:49:57 by namkim           ###   ########.fr       */
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
		sign = stat(addr, &sb);	//호출 성공시 0, 실패시 -1 & errno set
		if (sign == 0)
		{
			//먼저 권한체크 : 읽기 / 실행일 때 각각 다름....
			//만약 권한이 없다면 : continue;
			//id user로 했을 때 group 권한을 다 줬는데 왜 안 읽히는지...?
							//000중 어느쪽을 기준으로 권한 체크해야하는지?
							//우선은 소유주를 기준으로 체크
			//만약 권한이 있을 때 (실행가능한 상태일 때) -- but 만약 권한이 없더라도 실행은 하는게 맞는 것 같다. 왜? errno받아야 됨.
			if ((sb.st_mode & S_IXUSR) != 0)
			{
				res = addr;
				printf("addr: %s\n", res);
				execve(res, NULL, NULL);
			}
			else
				data->status = -5; //#define no permissioin
			return (res);
		}
		free(addr);
		i++;
	}
	return (res);
}
