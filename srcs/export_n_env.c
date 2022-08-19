/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_n_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:54:24 by namkim            #+#    #+#             */
/*   Updated: 2022/08/19 12:24:16 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	check_args(char	*target, char chr)
{
	int		len;
	char	*divider;

	len = get_env_len(target);
	if (len < 1)
		return (FALSE);
	if (chr == 'e')
	{
		divider = ft_strchr(target, '=');
		if (divider == NULL || *divider == '\0')
			return (FALSE);
	}
	return (TRUE);
}
//expansion의 경우 원래 (space), ':', '/' 등이 구분문자로 기능, But 우리는 : / 등을 해석하지 않기 때문에 그냥 space로만 expansion 할 것임!
//expansion의 경우 ""와 ''는 전부 shell prompt의 expansion 규칙을 따르는 듯 하다.
//복수의 argument가능, expansion 있음. value로 빈문자열 입력 가능. '='를 입력하지 않으면 무효처리
//export만 입력하는 경우
//로컬변수를 환경변수로 변경하는 명령어 -> 먼저 key를 등록하고, 로컬변수를 등록하는 순서로 환경변수로 등록할 수도 있다ㄸㄹㄹ...
//로컬변수를 사용할지 여부를 결정해야할 듯
void	ft_export(char **args, char	**envp)
{
	int		i;
	int		len;
	char	*key;


	i = 1;
	while (args[i])
	{
		//key & value -> 문법이 맞는지 확인
		//value expansion --> expansion해서 들어올 것 (참고로 key도 expansion한다)
		//key를 분리해서 존재하는지 확인
		//존재하면, 원래 있는 걸 지우고, 그 자리에 삽입
		//존재하지 않으면, 삽입 가능한지 체크하고 배열이 다 차있으면, 다시 할당해서 (size + 10) 삽입
	}
}

void	ft_env(char **envp)
{
	if (!envp)
		return ;
	while (*envp)
		ft_printf("%s\n", *envp++);
}

//envp사이즈 관리할까...? 관리하는게 편할 것 같음.
//복수의 arguement 가능
//존재하지 않는 키 입력시 아무 일도 안 일어남
//이것도 마찬가지로 argument expansion 있음.... 아니 근데 다시 생각해보니까 원래 들어올때부터 당연히 expansion하는 것 같다...!
//envp에서 키 값이 같은 애가 있는지 찾는다
//있으면? 삭제: free하고 memcpy...
//실험 필요
void	unset(char **args, char **envp)
{
	int	i;
	int	e;

	i = 1;
	while (args[i])
	{
		e = 0;
		{
			if (ft_strncmp(args[i], envp[e], ft_strlen(args[i])) == 0)
			{
				if (envp[e][ft_strlen(args[i])] == '=')
				{
					free (envp[e]);
					while (envp[++e])	//만약 환경변수의 숫자를 관리한다면, 그냥 제일 끝에 있는 걸 여기 삽입할 수도 있을 것 같다.
						envp[e - 1] = envp[e];
					envp[e] = NULL;
					return ;
				}
			}
			e++;
		}
		i++;
	}
}

//exit함수 argument : 종료코드 - argument가 하나를 넘어가면, bash: exit: too many arguments< 이런 오류메세지가 뜬다.
//종료코드는 0~255 -> 이 범위를 넘어가면 오버플로우 된다 ex. 256 -> 0으로 돌아옴
//이 때 코드가 바로 exit_status

//pwd : argument를 몇개 넣든 무시하는 것 같다
//a=$(pwd) < 이런 식의 사용이 가능하지만! 우리는 괄호를 해석하지 않는다...
//대문자로도 된다!
//cd 할 때마다 env에 PWD와 OLDPWD가 업데이트 된다
