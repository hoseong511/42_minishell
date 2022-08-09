#include "main.h"
#include <stdio.h>

// char	*match_env(char *keystr, t_list *data)
// {
// 	while (data)
// 	{
// 		if (keystr == ((t_env *)data->content)->key)
// 			return (((t_env *)data->content)->value);
// 		data = data->next;
// 	}
// 	return (NULL);
// }
// char	*replace_env(char *str, char *keystr)
// {
// 	char	*var;
// 	char	*prev;
// 	char	*next;
// 	char	*res;
// 	res = NULL;
// 	var = ft_strnstr(str, keystr, ft_strlen(str));
// 	if (var)
// 	{
// 		prev = ft_strndup(str, str - var);
// 		next = ft_strdup(var + ft_strlen(var));
// 		var = match_env(keystr, data);
// 		if (var)
// 		{
// 			res = ft_strjoin(prev, var);
// 			free (prev);
// 			prev = res;
// 			res = ft_strjoin(prev, next);
// 		}
// 		free(prev);
// 		free(next);
// 	}
// 	return (res);
// }

static void	remove_char(char **dst, char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = i;
	while (str[j])
	{
		if (str[j] == c)
		{
			j++;
			continue ;
		}
		*dst[i++] = str[j];
		j++;
	}
}

void	replace_s_quote(t_list **token, char *str)
{
	char	*a = ft_strchr(str, '\'');
	char	*tar;

	tar = (char *)(*token)->content;
	if (a)
	{
		tar += a - str;
		remove_char(&tar, a, '\'');
	}
	printf("%s\n", (char *)(*token)->content);
}

void	replace_d_quote(t_list **token, char *str)
{
	char	*a = ft_strchr(str, '\'');
	// char	*b = ft_strchr(str, '\"');
	char	*tar;

	tar = (char *)(*token)->content;
	if (a)
	{
		tar += a - str;
		remove_char(&tar, a, '\'');
	}
	printf("%s\n", (char *)(*token)->content);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*data;
	t_list	*token;
	char	*str;

	(void)argc;
	(void)envp;
	data = get_env(envp);
	token = tokenizer(argv[1]);
	while (token)
	{
		str = (char *)token->content;
		// if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		// 	replace_s_quote(&token, str);
		printf("%s\n", str);
		token = token->next;
	}
}
