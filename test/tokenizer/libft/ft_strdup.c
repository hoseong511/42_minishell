/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:00:38 by hossong           #+#    #+#             */
/*   Updated: 2022/08/10 16:08:03 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t slen)
{
	char	*dst;

	if (!s1 || slen == 0)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * (slen + 1));
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s1, slen + 1);
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	slen;

	if (!s1)
		return (NULL);
	slen = ft_strlen(s1);
	dst = (char *)malloc(sizeof(char) * (slen + 1));
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s1, slen + 1);
	return (dst);
}
