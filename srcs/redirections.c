/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:04:20 by namkim            #+#    #+#             */
/*   Updated: 2022/08/19 17:00:33 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	redirection_in(char *filepath)
{
	int			fd;
	int			sign;
	struct stat	sb;

	if (!filepath)
		ft_error("Syntax Error\n");
	printf("filepath : %s\n", filepath);
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		sign = stat(filepath, &sb);
		if (sign == 0)
			printf("%s: %s\n", filepath, "Permission Denied");
		else
			printf("%s: %s\n", filepath, strerror(errno));
		exit(1);
	}
	else
	{
		if (dup2(fd, 0) < 0)
			ft_perror("Dup2", errno);
		close(fd);
	}
}

void	redirection_out(char *filepath)
{
	int		fd;

	if (!filepath)
		ft_error("Syntax Error\n");
	fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("%s: %s\n", filepath, "Permission Denied");
		exit(1);
	}
	else
	{
		if (dup2(fd, 1) < 0)
			ft_perror("Dup2", errno);
		close(fd);
	}
}

void	redirection_append(char *filepath)
{
	int		fd;

	if (!filepath)
		ft_error("Syntax Error\n");
	fd = open(filepath, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("%s: %s\n", filepath, "Permission Denied");
		exit(1);
	}
	else
	{
		if (dup2(fd, 1) < 0)
			ft_perror("Dup2", errno);
		close(fd);
	}
}

void	redirection_heredoc(char *end_of_file)
{
	int		fd;
	char	*str;

	fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_error("Heredoc open error\n");
	str = NULL;
	char *tar = ft_strjoin(end_of_file, "\n");
	while (TRUE)
	{
		write(2, "> ", 2);
		str = get_next_line(0);
		if (ft_strncmp(str, tar, ft_strlen(tar) + 1) == 0)
		{
			free(str);
			free(tar);
			str = NULL;
			break ;
		}
		else
		{
			write(fd, str, ft_strlen(str));
			free (str);
			str = NULL;
		}
	}
	close(fd);
	fd = open(".tmp", O_RDONLY);	// 왜 꼭 다시 닫았다 열어야하는건지
	ft_dup2(fd, 0);
	unlink(".tmp");
	close(fd);
	// fd = open(".tmp", O_RDONLY);
	// str = get_next_line
}

//시작 지점부터 시작해서 redirection이 끝날때까지 while문
//check redirection 종류
//종류에 따라 unit실행
//반환(command가 시작하는 부분)
t_list	*redirection(t_list *args)
{
	t_list	*node;

	node = args;
	while (node)
	{
		if (((t_cmd2 *)node->content)->type < R_IN)
			return (node);
		else if (((t_cmd2 *)node->content)->type == R_IN)
			redirection_in(((t_cmd2 *)node->content)->str[1]);
		else if (((t_cmd2 *)node->content)->type == R_OUT)
			redirection_out(((t_cmd2 *)node->content)->str[1]);
		else if (((t_cmd2 *)node->content)->type == R_APPD)
			redirection_append(((t_cmd2 *)node->content)->str[1]);
		else if (((t_cmd2 *)node->content)->type == R_HEREDOC)
			redirection_heredoc(((t_cmd2 *)node->content)->str[1]);
		node = node->next;
	}
	return (node);
}
