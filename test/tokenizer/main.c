#include "main.h"
#include <stdio.h>

//환경변수 expansion
//single quote / doublequote 처리
//re_tokenize
// void	replace_double_quote(t_list *target)
// {
// 	char	*str;
// 	int		i;

// 	i = 0;
// 	str = (char *)target->content;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 		{
// 			while (str[++i] != '\'')
// 				;
// 			i++;
// 		}
// 		is_env_exist()
// 		i++;
// 	}
// }

void	replacement(char **str, t_list *data)  //한 token의 string
{
	int	 i;
	int	 len;
	char	q;
	t_list  *lst;
	t_list	*target;

	i = 0;
	len = 0;
	lst = NULL;
	while ((*str)[i + len])
	{
		if ((*str)[i + len] == '\"' || (*str)[i + len] == '\'')
		{
			if (len == 0)
			{
				q = (*str)[i];
				len = ++i;
				while((*str)[len] != q)
					len++;
				add_token(&lst, (*str), i, len);
				target = ft_lstlast(lst); //lstlast를 찾아서 q의 값에 따라 처리
				// if (q == '\'')
				// 	replace_single_quote(target);
				// else
				// 	replace_double_quote(target);
				i += len;
				len = 0;
			}
			else
			{
				add_token(&lst, (*str), i, len);
				target = ft_lstlast(lst); //lstlast를 찾아서 q의 값에 따라 처리
				//lstlast를 찾아서 env만 처리
				is_env_exist(&target->content, data);
				i += len;
				len = 0;
			}
		}
		else
			len++;
	}
	if ((*str)[i + len] == '\0' && str[i + len - 1])
	{
		add_token(&lst, (*str), i, len);
		target = ft_lstlast(lst);
		is_env_exist(&target->content, data);
	}
	char	*temp;
	temp = NULL;
	free(*str);
	*str = NULL;
	while (lst)
	{
		temp = *str;
		*str = ft_strjoin(temp, (char *)lst->content);
		if (temp)
			free(temp);
		lst = lst->next;
	}
}

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
		replacement(&str, data);
		printf("str: %s\n", str);
		token = token->next;
	}
}
