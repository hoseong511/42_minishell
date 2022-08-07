/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:42:38 by hossong           #+#    #+#             */
/*   Updated: 2021/11/25 12:03:13 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*dst;
	size_t	len;
	long	num;

	len = ft_intlen(n);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	dst[len] = '\0';
	num = n;
	if (num < 0)
	{
		dst[0] = '-';
		num = num * -1;
	}
	else if (num == 0)
		dst[0] = '0';
	while (len-- && num > 0)
	{
		dst[len] = (num % 10) + '0';
		num /= 10;
	}
	return (dst);
}
