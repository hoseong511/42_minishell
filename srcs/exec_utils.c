/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:09:37 by namkim            #+#    #+#             */
/*   Updated: 2022/08/18 18:13:36 by hossong          ###   ########.fr       */
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
char	**get_path(char **path)
{
	char	**res;
	char	*path_value;

	path_value = match_env("PATH", path);
	printf("path : %s\n", path_value);
	res = ft_split(path_value, ':');
	free(path_value);
	printf("res[1] : %s\n", res[1]);
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
char	*get_exe_file(char	**envp, char *cmd)
{
	char		*res;
	char		*addr;
	int			i;
	struct stat	sb;
	int			sign;
	char		**path;

	i = 0;
	res = NULL;
	printf("%s\n", envp[1]);
	path = get_path(envp);
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
				exit(1);
			return (res);
		}
		free(addr);
		i++;
	}
	return (res);
}
