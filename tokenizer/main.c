#include "../includes/main.h"
#include <stdio.h>

//환경변수 expansion
//single quote / doublequote 처리
//re_tokenize
void	replace_quote(t_list *target, char quote, t_list *data)
{
	char	*str;
	int		strlen;
	int		i;

	i = 0;
	str = (char *)target->content;
	strlen = ft_strlen(str);
	str = ft_memmove(str, str, strlen - 1);
	str[strlen - 1] = '\0';
	if (quote == '\"')
		is_env_exist(target, data);
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
				len = ++i;
				while ((*str)[len] != q)
					len++;
				add_token(&lst, (*str), i, len);
				target = ft_lstlast(lst); //lstlast를 찾아서 q의 값에 따라 처리
				replace_quote(target, q, data);
				i += len;
				len = 0;
			}
			else
			{
				add_token(&lst, (*str), i, len);
				target = ft_lstlast(lst);
				is_env_exist(target, data);
				i += len;
				len = 0;
			}
		}
		else
			len++;
	}
	if ((*str)[i + len] == '\0' && (*str)[i + len - 1])
	{
		add_token(&lst, (*str), i, len);
		target = ft_lstlast(lst);
		is_env_exist(target, data);
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
	t_data	*data;
	t_list	*token;
	t_list	*node;
	char	*str;

	(void)argc;
	(void)envp;
	data = init_shell(envp);
	data->tokenlist = tokenizer(argv[1]);
	token = data->tokenlist;
	while (token)
	{
		str = (char *)token->content;
		replacement(&str, data->envlist);
		printf("str: %s\n", str);
		token = token->next;
	}
	data->cmdlist = parser(data);
	node = data->cmdlist;
	while (node)
	{
		printf("[%d] %s\n",\
			((t_cmd *)(node->content))->type, (char *)((t_cmd *)(node->content))->str);
		node = node->next;
	}
}
