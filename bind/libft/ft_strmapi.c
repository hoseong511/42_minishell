/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:30:21 by hossong           #+#    #+#             */
/*   Updated: 2021/11/24 12:30:18 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dst;
	unsigned int	i;
	size_t			slen;

	if (s == NULL || f == NULL)
		return (NULL);
	slen = ft_strlen(s);
	i = 0;
	dst = (char *)malloc(sizeof(char) * (slen + 1));
	if (dst == NULL)
		return (NULL);
	while (i < slen)
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
