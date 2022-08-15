/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:55:55 by hossong           #+#    #+#             */
/*   Updated: 2021/11/26 23:07:09 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_target(char const *s, char c, char *target)
{
	int	count;

	count = 0;
	if (ft_strncmp("sep", target, 3) == 0)
	{
		while (*s && *(s++) == c)
			count++;
	}
	else if (ft_strncmp("word", target, 4) == 0)
	{
		while (*s && *(s++) != c)
			count++;
	}
	return (count);
}

static int	count_list(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		i += count_target(s + i, c, "sep");
		if (s[i] != '\0')
			count += 1;
		i += count_target(s + i, c, "word");
	}
	return (count);
}

static char	**clear_lst(char **lst, int i)
{
	while (i--)
		free(lst[i]);
	free(lst);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char			**result;
	unsigned int	i;
	unsigned int	j;

	if (s == NULL)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_list(s, c) + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		i += count_target(s + i, c, "sep");
		if (s[i] != '\0')
		{
			result[j] = ft_substr(s, i, count_target(s + i, c, "word"));
			if (result[j++] == NULL)
				return (clear_lst(result, j));
		}
		i += count_target(s + i, c, "word");
	}
	result[j] = NULL;
	return (result);
}
