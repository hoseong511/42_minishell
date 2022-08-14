/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:43:27 by hossong           #+#    #+#             */
/*   Updated: 2022/08/14 10:30:12 by hossong          ###   ########.fr       */
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
# define TRUE 1
# define FALSE 0


typedef enum e_type
{
	ARGS,
	PIPE,
	R_IN,
	R_OUT,
	R_APPD,
	R_HEREDOC,
	R_ARG
}	t_type;

typedef struct s_cmd
{
	char		*str;
	t_type		type;
}	t_cmd;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_data
{
	t_list		*envlist;
	t_list		*tokenlist;
	t_list		*cmdlist;
	int			pip_cnt;	//or 실행해야하는 process의 수
	int			status;
							//이후 exit status등 필요한 데이터 추가
}	t_data;

void	ft_error(char *err_msg);

int		check_quote(char *str);
char	*replace_env(char *str, char *keystr, t_list *data);
char	*match_env(char *keystr, t_list *data);
void	is_env_exist(t_list *target, t_list *data);
int		is_valid_env_name(char c, int idx);
t_list	*get_env(char **envp);

/* control data */
t_data	*init_data(char **envp);
void	load_data(t_data *data, char *str);

/* replacement */
void	replace_quote(t_list *target, char quote, t_list *data);
void	replacement(char **str, t_list *data);

/* tokenizer */
void	add_token(t_list **lst, char *str, size_t len);
int		check_redir(t_list **lst, char *str);
int		get_quote_end_idx(t_list **lst, char *str);
int		add_end_token(t_list **lst, char *str);

/* parser */
void	add_cmd(t_list **lst, char *str, t_type type);
t_type	get_cmd_type(char *str);
t_list	*lexer(t_data *data);
t_list	*tokenizer(char *str);
t_list	*relocate_type(t_list *cmdlist);
void	insert(t_list *a, t_list *b);
void	push(t_list **list, t_list *node);
t_list	*pop(t_list **list);



#endif
