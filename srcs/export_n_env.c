/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_n_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:54:24 by namkim            #+#    #+#             */
/*   Updated: 2022/08/19 17:21:19 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

// int	check_args(char	*target, char chr)	- 현재 안 씀
// {
// 	int		len;
// 	char	*divider;

// 	len = get_env_len(target);
// 	if (len < 1)
// 		return (FALSE);
// 	if (chr == 'e')
// 	{
// 		divider = ft_strchr(target, '=');
// 		if (divider == NULL || *divider == '\0')
// 			return (FALSE);
// 	}
// 	return (TRUE);
// }

//expansion의 경우 원래 (space), ':', '/' 등이 구분문자로 기능, But 우리는 : / 등을 해석하지 않기 때문에 그냥 space로만 expansion 할 것임!
//expansion의 경우 ""와 ''는 전부 shell prompt의 expansion 규칙을 따르는 듯 하다.
//복수의 argument가능, expansion 있음. value로 빈문자열 입력 가능. '='를 입력하지 않으면 무효처리
//export만 입력하는 경우
//로컬변수를 환경변수로 변경하는 명령어 -> 먼저 key를 등록하고, 로컬변수를 등록하는 순서로 환경변수로 등록할 수도 있다ㄸㄹㄹ...
//로컬변수를 사용할지 여부를 결정해야할 듯
//value expansion --> expansion해서 들어올 것 (참고로 key도 expansion한다)
//key를 분리해서 존재하는지 확인
//존재하면, 원래 있는 걸 지우고, 그 자리에 삽입
//존재하지 않으면, 삽입 가능한지 체크하고 배열이 다 차있으면, 다시 할당해서 (size + 10) 삽입
void	ft_export(char **args, t_data *data)
{
	int		i;
	int		len;
	int		idx;
	char	*key;

	i = 1;
	if (!args[1])
		ft_env(args, data->envlist);//왜인지 알파벳 순서대로 보여준다.. declare -x 라는 포맷과 함께
	while (args[i])
	{
		//key & value -> 문법이 맞는지 확인
		len = get_env_len(args[i]);
		if (args[i][len] == '=')
		{
			key = ft_strdnup(args[i], len);
			idx = get_env_idx(key, data->envlist);
			if (idx >= 0)
			{
				free(data->envlist[idx]);
				data->envlist[idx] = ft_strdup(args[i]);	//복제해서 넣는다
			}
			else
				add_env_to_envlist(args[i], data);
			free(key);
		}
		//else : 로컬 변수를 쓴다면...
	}
}

void	ft_env(char **args, t_data *data)
{
	char	**envp;

	envp = data->envlist;
	if (args[1])
	{
		if (args[0][2] == 'n')
			printf("env: %s: No such file or directory\n", args[1]);
		if (args[0][2] == 'x')
			printf("export: `%s': not a valid identifier\n", args[1]);
		exit(1);
	}
	if (!envp)
		return ;
	while (*envp)
	{
		if (args[0][2] == 'x')
			printf("declare -x ");
		printf("%s\n", *envp++);
	}
	if (args[0][2] == 'n')
		printf("_=/usr/bin/%s\n", args[0]);
}

//envp사이즈 관리할까...? 관리하는게 편할 것 같음.
//복수의 arguement 가능
//존재하지 않는 키 입력시 아무 일도 안 일어남
//이것도 마찬가지로 argument expansion 있음.... 아니 근데 다시 생각해보니까 원래 들어올때부터 당연히 expansion하는 것 같다...!
//envp에서 키 값이 같은 애가 있는지 찾는다
//있으면? 삭제: free하고 memcpy...
//실험 필요
void	ft_unset(char **args, t_data *data)
{
	int		i;
	int		e;
	char	**envp;
	int		idx;

	i = 1;
	envp = data->envlist;
	while (args[i])
	{
		idx = get_env_idx(args[i], data->envlist);
		if (idx >= 0)
		{
			free (envp[idx]);
			envp[idx] = envp[data->envlist_cnt - 1];
			envp[data->envlist_cnt - 1] = NULL;
			data->envlist_cnt--;
			return ;
		}
		i++;
	}
}

//exit함수 argument : 종료코드 - argument가 하나를 넘어가면, bash: exit: too many arguments< 이런 오류메세지가 뜬다.
//종료코드는 0~255 -> 이 범위를 넘어가면 오버플로우 된다 ex. 256 -> 0으로 돌아옴
//이 때 코드가 바로 exit_status

//pwd : argument를 몇개 넣든 무시하는 것 같다
//대문자로도 된다! < 모든 대소문자의 조합으로 가능하다... 대체 왜...?
//알고보니...? 모든 명령어는 대소문자 관계없이 실행이 가능했다... 왜????
//touch B < 파일은 찾을 수 없는데, cat은 가능하다... 왜????
void	ft_pwd(char **args)
{
	char	*res;

	if (!args || !args[0])
		return ;	//or error
	else
	{
		res = getcwd(NULL, 0);
		if (!res)
			ft_error("Couldn't get working directory\n");
		printf("%s\n", res);
		free(res);
	}

}
//a=$(pwd) < 이런 식의 사용이 가능하지만! 우리는 괄호를 해석하지 않는다...
//cd 할 때마다 env에 PWD와 OLDPWD가 업데이트 된다 (bash는 OLDPWD 없음)

//cd - : 이전 위치로(할 필요 없음)
//cd ~ : home directory로(할 필요 없음)
//cd with no args : home directory로(할 필요 없지 않을까...?)
//위치로 옮기고, env update
void	ft_cd(char **args, t_data *data)
{
	char	*path;
	char	*pwd;
	int		sign;

	if (!args[1])
		path = match_env("HOME", data->envlist);	//확인할 것
	else
		path = args[1];
	sign = chdir(path);
	if (sign == 0)
	{
		free(path);
		pwd = getcwd(NULL, 0);
		if (!pwd)
			ft_error("Couldn't get working directory\n");
		path = ft_strjoin("PWD=", pwd);
		ft_export(&path, data);
		free(pwd);
		free(path);
	}
	else
	{
		printf("cd: %s: No such file or directory\n", args[1]);
		exit(1);
	}
}

//여기서 모든 메모리 해제를 넣어줘야 하는지...? 어차피 exit가 모두 처리할건데도?
void	ft_exit(char **args)
{
	printf("exit\n");
	exit(0);
}

void	ft_echo(char **args)
{
	int	i;

	i = 1;
	if (ft_strncmp(args[i], "-n", 3) == 0)
		i++;
	while (args[i + 1])
	{
		write(1, args[i], ft_strlen(args[i]));
		write(1, " ", 1);
		i++;
	}
	write(1, args[i], ft_strlen(args[i]));
	if (ft_strncmp(args[1], "-n", 3) != 0)
		write(1, '\n', 1);
}
