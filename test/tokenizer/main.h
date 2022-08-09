#ifndef MAIN_H
# define MAIN_H

# include <readline/readline.h>
# include "./libft/libft.h"

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

#endif