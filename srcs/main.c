/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:42:28 by hossong           #+#    #+#             */
/*   Updated: 2022/08/23 13:34:19 by namkim           ###   ########.fr       */
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

static void	set_initial_status(t_data *data)
{
	set_termattr(data->set);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	eof(void)
{
	printf("\033[1A");
	printf("\033[10C");
	ft_exit(NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char				*str;
	t_data				*data;

	(void) argv;
	if (argc != 1)
		ft_error("Too much argument!\n");
	data = init_data(envp);
	def_termattr(data);
	while (1)
	{
		set_initial_status(data);
		str = readline("mini-0.8$ ");
		if (!str)
			eof();
		if (*str)
			add_history(str);
		load_data(data, str);
		execution(data);
		printf("g_status : %d\n", g_status);
		free(str);
		re_initialize(data);
	}
	return (0);
}
