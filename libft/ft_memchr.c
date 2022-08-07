/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:55:40 by hossong           #+#    #+#             */
/*   Updated: 2021/11/27 10:39:12 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ps;
	size_t				i;

	ps = s;
	i = 0;
	while (i < n)
	{
		if (ps[i] == (unsigned char)c)
			return ((void *)&ps[i]);
		i++;
	}
	return (NULL);
}
