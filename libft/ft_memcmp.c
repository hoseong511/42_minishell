/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:08:13 by hossong           #+#    #+#             */
/*   Updated: 2021/11/21 23:32:56 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*ps1;
	const char	*ps2;

	if (n == 0)
		return (0);
	ps1 = s1;
	ps2 = s2;
	while (--n && *ps1 == *ps2)
	{
		ps1++;
		ps2++;
	}
	return ((unsigned char)*ps1 - (unsigned char)*ps2);
}
