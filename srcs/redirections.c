/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:04:20 by namkim            #+#    #+#             */
/*   Updated: 2022/08/18 19:36:50 by namkim           ###   ########.fr       */
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
			printf("%s: %s", filepath, strerror(errno));
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
	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("%s: %s", filepath, "Permission Denied");
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
	fd = open(filepath, O_WRONLY | O_APPEND | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("%s: %s", filepath, "Permission Denied");
		exit(1);
	}
	else
	{
		if (dup2(fd, 1) < 0)
			ft_perror("Dup2", errno);
		close(fd);
	}
}

//일단 파일을 만든다 - 파일 이름 어떻게?
//여기서 다시 readline해야하는 것 같은디?
//readline으로 한 줄 한 줄 가져옴
	//-> 그 내용을 그 때마다 한 줄 한 줄 씀!
//EOF를 만났나?
//만났으면 파일을 닫고, dup...
//그런데 파일은 어떻게 삭제하지...?
/*
	unlink : If one or more process have the file open
	when the last link is removed,the link is removed,
	but the removal of the file is delayed until all references to it have been closed.
*/
void	redirection_heredoc(char *end_of_file)
{
	int	fd;

	fd = open(".tmp", O_RDWR | O_CREAT, 644);

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
			printf("this is HEREDOC\n");
//			redirection_in(((t_cmd2 *)node->next->content)->str);
		node = node->next;
	}
	return (node);
}
