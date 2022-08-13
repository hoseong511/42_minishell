/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:42:28 by hossong           #+#    #+#             */
/*   Updated: 2022/08/13 14:58:08 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	// char	*pwd_name;
	// pid_t	pid;
	// char	name[BUF_SIZE];
	// char	**line;
	t_error	is_error;
	t_list	*data;
	t_env	*env;

	(void)argc;
	(void)argv;
	printf("==minishell==\n");
	data = get_env(envp);
	while (1)
	{
		if (!data)
			break ;
		env = (t_env *)data->content;
		printf("key: %s value: %s\n", env->key, env->value);
		data = data->next;
	}
	while (1)
	{
		str = readline("mini-0.1$ ");
		/*	1. 해석하지 말아할 문자 (닫히지 않은 quote / '\') 가 포함되어 있는지
			2. quote 처리? -> ' ", "" ''
			3. 환경변수 치환
		*/
		is_error = check_quote(str);
		// replace_env(&str, data);
		// if (ft_strchr(str, '|'))
		// {
		// 	line = ft_split(str, '|');
		// 	int i = 0;
		// 	while (i < 2)
		// 	{
		// 		char **arg;
		// 		if (i == 0)
		// 		{
		// 			arg = ft_split(line[0], ' ');
		// 			pid = fork();
		// 			if (pid == 0)
		// 			{
		// 				execve("/bin/echo", arg, envp);
		// 				printf("%s\n", strerror(errno));
		// 			}
		// 			else if (pid < 0)
		// 				printf("%d, %s\n", errno, strerror(errno));
		// 			else
		// 				wait(NULL);
		// 		}
		// 		else
		// 		{
		// 			arg = ft_split(line[1], ' ');
		// 			pid = fork();
		// 			if (pid == 0)
		// 			{
		// 				execve("/usr/bin/grep", arg, envp);
		// 				printf("%s\n", strerror(errno));
		// 			}
		// 			else if (pid < 0)
		// 				printf("%d, %s\n", errno, strerror(errno));
		// 			else
		// 				wait(NULL);
		// 		}
		// 		i++;
		// 	}
		// }
		// else
		// 	line = ft_split(str, ' ');
		// if (*str)
		// 	add_history(str);
		// if (ft_strncmp(line[0], "exit\0", 5) == 0)
		// {
		// 	printf("exit\n");
		// 	break ;
		// }
		// else if (ft_strncmp(line[0], "pwd\0", 4) == 0)
		// {
		// 	pid = fork();
		// 	if (pid == 0)
		// 	{
		// 		pwd_name = getcwd(name, BUF_SIZE);
		// 		if (pwd_name)
		// 		{
		// 			printf("%s\n", pwd_name);
		// 			exit(0);
		// 		}
		// 		printf("%d, %s\n", errno, strerror(errno));
		// 	}
		// 	else if (pid < 0)
		// 		printf("%d, %s\n", errno, strerror(errno));
		// 	else
		// 		wait(NULL);
		// }
		// else if (ft_strncmp(line[0], "echo\0", 5) == 0)
		// {
		// 	pid = fork();
		// 	if (pid == 0)
		// 	{
		// 		execve("/bin/echo", line, envp);
		// 		printf("%s\n", strerror(errno));
		// 	}
		// 	else if (pid < 0)
		// 		printf("%d, %s\n", errno, strerror(errno));
		// 	else
		// 		wait(NULL);
		// }
		// free(str);
	}
	return (0);
}
