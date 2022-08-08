/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:43:27 by hossong           #+#    #+#             */
/*   Updated: 2022/08/07 20:29:21 by hossong          ###   ########.fr       */
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

# include "libft/libft.h"

# define BUF_SIZE 1024
# define INHIBIT "'\"\\;'`"

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

char	*ft_strstr(char *str, char *to_find);

#endif