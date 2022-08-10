#ifndef MAIN_H
# define MAIN_H

# include <readline/readline.h>
# include "./libft/libft.h"
# define TRUE 1
# define FALSE 0

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef enum e_type
{
	LESS = 0,
	GREAT,
	LESSLESS,
	GREATGREAT,
	PIPE,

}	t_type;

void	add_token(t_list **lst, char *str, int start, size_t len);
int		check_quote(char *str, int i);
int		check_redir(t_list **lst, char *str, int start);
void	ft_error(char *err_msg);
t_list	*get_env(char **envp);
t_list	*tokenizer(char *str);

char	*replace_env(char *str, char *keystr, t_list *data);
char	*match_env(char *keystr, t_list *data);
void	is_env_exist(t_list *target, t_list *data);


#endif