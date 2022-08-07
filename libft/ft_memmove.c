/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:49:30 by hossong           #+#    #+#             */
/*   Updated: 2021/11/25 11:43:06 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pdst;
	const unsigned char	*psrc;
	size_t				i;

	if (dst == src || len == 0)
		return (dst);
	pdst = dst;
	psrc = src;
	i = 0;
	if (src < dst)
	{
		while (0 < len--)
			pdst[len] = psrc[len];
	}
	else
	{
		while (i < len)
		{
			pdst[i] = psrc[i];
			i++;
		}
	}
	return (dst);
}
