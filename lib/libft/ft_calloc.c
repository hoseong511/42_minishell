/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:19:51 by hossong           #+#    #+#             */
/*   Updated: 2021/11/23 11:56:03 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dst;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	dst = malloc(count * size);
	if (dst == NULL)
		return (NULL);
	ft_bzero(dst, count * size);
	return (dst);
}
