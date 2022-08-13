#ifndef MAIN_H
# define MAIN_H

# include <readline/readline.h>
# include "./libft/libft.h"
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

typedef struct s_data
{
	t_list		*envlist;
	t_list		*tokenlist;
	t_list		*cmdlist;
	int			pip_cnt;	//or 실행해야하는 process의 수
							//이후 exit status등 필요한 데이터 추가
}	t_data;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;


t_data	*init_shell(char **envp);

void	add_token(t_list **lst, char *str, int start, size_t len);
int		check_quote(char *str, int i);
int		check_redir(t_list **lst, char *str, int start);
void	ft_error(char *err_msg);
t_list	*get_env(char **envp);
t_list	*tokenizer(char *str);

char	*replace_env(char *str, char *keystr, t_list *data);
char	*match_env(char *keystr, t_list *data);
void	is_env_exist(void **target, t_list *data);

#endif
