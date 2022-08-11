#include "main.h"
#include <stdio.h>

// 환경변수 expansion
// single quote / doublequote 처리
// re_tokenize
void	replace_quote(t_list *target, char quote, t_list *data)
{
	char	*str;
	int		len;

	str = (char *)target->content;
	len = ft_strlen(str) - 2;
	ft_memmove(str, str + 1, len);
	str[len] = '\0';
	printf("target->content: %s\n", target->content);
	if (quote == '\"')
		is_env_exist(&target->content, data);
}

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
				len = i + 1;
				while ((*str)[len] != q)
					len++;
				printf("start-end-%c:%c\n", (*str)[i], (*str)[i + len]);
				add_token(&lst, (*str), i, len + 1);
				target = ft_lstlast(lst); //lstlast를 찾아서 q의 값에 따라 처리
				printf("t_str : %s\n", (char *)target->content);
				if (q == '\'')
					replace_quote(target, '\'', data);
				else
					replace_quote(target, '\"', data);
				i += (len + 1);
				len = 0;
			}
			else
			{
				add_token(&lst, (*str), i, len);
				target = ft_lstlast(lst);
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

int	main(int argc, char **argv, char **envp)
{
	t_list	*data;
	t_list	*token;
	char	*str;
	int		i;

	(void)argc;
	(void)envp;
	data = get_env(envp);
	token = tokenizer(argv[1]);
	i = 0;
	while (token)
	{
		str = (char *)token->content;
		replacement(&str, data);
		printf("[%d] %s\n", i, str);
		token = token->next;
		i++;
	}
}
