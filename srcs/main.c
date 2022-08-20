/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:42:28 by hossong           #+#    #+#             */
/*   Updated: 2022/08/20 21:58:49 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	g_status;

int	main(int argc, char **argv, char **envp)
{
	struct termios		term;
	char				*str;
	t_data				*data;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	(void) argv;
	if (argc != 1)
		ft_error("Too much argument!\n");
	printf("==minishell==\n");
	data = init_data(envp);
	while (1)
	{
		str = readline("mini-0.8$ ");
		if (!str)
		{
			printf("\033[1A"); // 커서를 위로 한 줄 올린다.
			printf("\033[10C"); // 커서를 10만큼 앞으로 전진시킨다.
			ft_exit();
		}
		if (*str)
			add_history(str);
		load_data(data, str);
		if (data->status == FALSE)
			continue ;
		execution(data);
		// free
		free(str);
	}
	free_data(data);
	return (0);
}
