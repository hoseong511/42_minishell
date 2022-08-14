/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:46:57 by namkim            #+#    #+#             */
/*   Updated: 2022/08/14 03:06:47 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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
				add_token(&lst, (*str) + i, len);
				target = ft_lstlast(lst); //lstlast를 찾아서 q의 값에 따라 처리
				replace_quote(target, q, data);
				i += len;
				len = 0;
			}
			else
			{
				add_token(&lst, (*str) + i, len);
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
		add_token(&lst, (*str) + i, len);
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

t_data	*init_data(char **envp)
{
	t_data	*res;

	res = malloc(sizeof(t_data));
	if (!res)
		ft_error("Malloc Error While Initialize\n");
	res->envlist = get_env(envp);
	res->tokenlist = NULL;
	res->cmdlist = NULL;
	res->pip_cnt = 0;
	res->status = TRUE;
	return (res);
}

void	load_data(t_data *data, char *str)
{
	t_list	*token;
	t_list	*node;

	data->status = check_quote(str);
	if (data->status == FALSE)
		return ;
	data->tokenlist = tokenizer(str);
	token = data->tokenlist;
	while (token)
	{
		str = (char *)token->content;
		// replacement(&str, data->envlist);
		printf("str: %s\n", str);
		token = token->next;
	}
	data->cmdlist = lexer(data);
	node = data->cmdlist;
	while (node)
	{
		printf("[%d] %s\n",\
			((t_cmd *)(node->content))->type, (char *)((t_cmd *)(node->content))->str);
		node = node->next;
	}
	data->cmdlist = relocate_type(data->cmdlist);
	t_list	*reloc = data->cmdlist;
	while (reloc)
	{
		printf("%s\n", ((t_cmd *)(reloc->content))->str);
		reloc = reloc->next;
	}
}
