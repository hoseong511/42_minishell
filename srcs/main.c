/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:42:28 by hossong           #+#    #+#             */
/*   Updated: 2022/08/22 15:21:05 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	g_status;

static	void	def_termattr(t_data *data)
{
	if (tcgetattr(STDIN_FILENO, &data->set) != 0)
		ft_perror("tcgetattr", errno);
	data->save = data->set;
	data->set.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &data->set) != 0)
		ft_perror("tcsetattr", errno);
}

void	set_termattr(struct termios term)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		ft_perror("tcsetattr", errno);
}

int	main(int argc, char **argv, char **envp)
{
	char				*str;
	t_data				*data;

	(void) argv;
	if (argc != 1)
		ft_error("Too much argument!\n");
	printf("==minishell==\n");
	data = init_data(envp);
	def_termattr(data);
	while (1)
	{
		set_termattr(data->set);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		str = readline("mini-0.8$ ");
		if (!str)
		{
			printf("\033[1A");
			printf("\033[10C");
			ft_exit(NULL);
		}
		if (*str)
			add_history(str);
		load_data(data, str);
		if (data->status == FALSE)
		{
			data->status = TRUE;
			continue ;
		}
		execution(data);
		// free
		free(str);
	}
	free_data(data);
	return (0);
}
