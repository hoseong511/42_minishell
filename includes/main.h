/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:43:27 by hossong           #+#    #+#             */
/*   Updated: 2022/08/13 14:44:59 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <sys/errno.h>

# include "../lib/libft/libft.h"

# define BUF_SIZE 1024
# define INHIBIT "\\;`"

typedef enum e_error
{
	ERROR = -1,
	SUCCESS
}	t_error;

typedef struct s_cmd
{
	char	**content;
}	t_cmd;

typedef struct s_data
{
	char	**dir;
	int		cmd_count;
	t_cmd	*cmd;
}	t_data;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

char	*ft_strstr(char *str, char *to_find);
t_error	check_quote(char *str);
void	replace_env(char **str, t_list *data);
t_list	*get_env(char **envp);

#endif
