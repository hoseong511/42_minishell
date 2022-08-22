/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:43:27 by hossong           #+#    #+#             */
/*   Updated: 2022/08/22 10:02:19 by namkim           ###   ########.fr       */
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
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>

# include "../lib/libft/libft.h"

# define TRUE 1
# define FALSE 0

extern int	g_status;

typedef enum e_type
{
	NONE = -1,
	ARGS,
	PIPE,
	R_IN,
	R_OUT,
	R_APPD,
	R_HEREDOC,
	R_ARG
}	t_type;

typedef enum e_built
{
	B_ECHO = 1,
	B_CD,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT
}	t_built;

typedef struct s_cmd
{
	char	*str;
	t_type	type;
}	t_cmd;

typedef struct s_cmd2
{
	char	**str;
	t_type	type;
}	t_cmd2;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_pipe
{
	int	fd[2];
}	t_pipe;

typedef struct s_proc
{
	pid_t	pid;
	int		status;
	t_pipe	pipe[2];
}	t_proc;

typedef struct s_data
{
	char				**envlist;
	int					envlist_size;
	int					envlist_cnt;
	t_list				*tokenlist;
	t_list				*cmdlist;
	int					cmd_cnt;
	int					status;
	int					exit_status;
	t_proc				*info;
	int					stdin_fd;
	int					stdout_fd;
	int					redir;
	struct termios		set;
	struct termios		save;
}	t_data;

void	ft_error0(char *err_msg);
void	ft_error(char *err_msg);
void	ft_error2(char *arg, char *err_msg);
void	ft_error3(char *arg, char *err_msg, int errcode);
void	ft_perror(char *err_msg, int err);
void	ft_dup2(int fd1, int fd2);
char	*match_env(char *keystr, char **envlist);
int		is_valid_env_name(char c, int idx);
char	**get_env(char **envp, t_data *data);
int		get_env_len(char *target);
void	replace_env(char **target, int start, int keysize, char **envp);
void	do_replace(t_list *com, int *i, int *j, char *target);
void	set_termattr(struct termios term);

/* control data */
t_data	*init_data(char **envp);
void	load_data(t_data *data, char *str);

/* replacement */
void	replace_quote(t_list *target, char quote, t_list *data);
void	replacement(char **str, t_list *data);

/* tokenizer */
void	add_token(t_list **lst, char *str, size_t len);
int		check_redir(t_list **lst, char *str);
int		add_end_token(t_list **lst, char *str);
int		get_quote_end_idx(char *str, int i);
int		add_quote_idx(char *str);

/* token utils */
void	print_t_cmds(t_list *tokenlist);

/* parser */
void	add_cmd(t_list **lst, char *str, t_type type);
void	add_cmd2(t_list **lst, char **str, t_type type);
t_type	get_cmd_type(char *str);
t_list	*lexer(t_data *data);
t_list	*tokenizer(char *str);
t_list	*relocate(t_list *tokenlist);
t_list	*bind(t_list *cmdlist);
void	insert(t_list **a, t_list *b);
t_list	*pop(t_list **list);
void	append_ab(t_list **lst, t_list *a, t_list *b);
void	insert_src(t_list **des, t_list **src, t_list **tmp);

/* syntax */
int		check_quote(char *str);
void	check_pipe_syntax(t_data *data);
void	check_redirection_syntax(t_data *data);

/* excute */
t_proc	*init_proc_info(void);
void	execution(t_data *data);
t_built	check_builtin(t_list *args);
void	exec_builtin(t_list *args, t_data *data);
void	exec_process(t_data *data, t_list *cmdlist);
void	parent_process(t_data *data, int depth);
void	child_process(t_data *data, t_list *c_node, int depth);
void	exec_arg(t_data *data, t_list *args);
void	pipe_io(t_data *data, int depth, int cmd_cnt);
char	*get_next_line(int fd);

/* redirection*/
void	init_pipe(t_data *data, int depth, int cnt);
void	redirection_in(char *filepath);
void	redirection_out(char *filepath);
void	redirection_append(char *filepath);
t_list	*redirection_left(t_data *data, t_list *args);
t_list	*redirection_right(t_list *args);

/*free*/
void	free_cmdlist(t_list *cmdlist);
void	free_tokenlist(t_data *data);
void	free_data(t_data *data);
void	free_cmd(t_list *cmdlist, char *tar);

/*replacement fix*/
void	do_replace_in_token(t_cmd *node, char **envp);
t_list	*split_words(char *target, int i, int j);

void	remove_quote(char **target, int startidx, int endidx);
char	*replace_key_to_value(char *str, int start, char *keystr, char **envp);
void	do_expansion(char **target, char **envp, char sign);
void	make_component(t_list **lst, char *src, int size);
char	*join_components(t_list *component);
int		count_env(char *str, char chr);

/* print utils */
void	print_t_cmds2(t_list *tokenlist);

/* execution utils */
char	**get_path(char **envlist);
char	*get_exe_file(char	**path, char *cmd);

/* built-in functions */
int		insert_env(char *arg, t_data *data);
void	ft_export(char **args, t_data *data);
void	ft_env(char **args, t_data *data);
void	ft_unset(char **args, t_data *data);
void	ft_pwd(char **args);
void	ft_cd(char **args, t_data *data);
//void	ft_exit(char **args);
void	ft_exit(char **args);
void	ft_echo(char **args);

/* control_env_array */
int		is_envlist_full(t_data *data);
int		add_env_to_envlist(char *env, t_data *data);
int		get_env_idx(char *keystr, char **envp);

/* signal */
void	signal_handler(int signal);
void	signal_handler_c(int signal);
void	signal_handler_d(int signal);

#endif
