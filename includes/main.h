/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:43:27 by hossong           #+#    #+#             */
/*   Updated: 2022/08/16 20:21:18 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>

# include "../lib/libft/libft.h"

# define BUF_SIZE 1024
# define TRUE 1
# define FALSE 0

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

typedef struct s_data
{
	t_list		*envlist;
	t_list		*tokenlist;
	t_list		*cmdlist;
	int			pip_cnt;
	int			status;
}	t_data;

void	ft_error(char *err_msg);

int		check_quote(char *str);
char	*match_env(char *keystr, t_list *data);
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
t_list	*relocate_type(t_data *data);
t_list	*bind_type(t_data *data);
void	insert(t_list *a, t_list *b);
void	push(t_list **list, t_list *node);
t_list	*pop(t_list **list);

/* excute */
void	execute_cmd(t_data *data);

/*free*/
void	free_cmdlist(t_data *data);
void	free_tokenlist(t_data *data);
void	free_data(t_data *data);
void	free_cmd(t_data *data, char *tar);

/*replacement fix*/
void	do_replace_in_token(t_cmd *node, t_list *envp);
void	remove_quote(char **target, int startidx, int endidx);
char	*replace_key_to_value(char *str, int start, char *keystr, t_list *data);
void	do_expansion(char **target, t_list *envp, char sign);
void	make_component(t_list **lst, char *src, int size);
char	*join_components(t_list *component);
void	process_quote(t_list *component, t_list *envp, char quote);
void	process_non_quote(t_list *component, t_list *envp);
int		count_env(char *str, char chr);

void	print_t_cmds2(t_list *tokenlist);

#endif
