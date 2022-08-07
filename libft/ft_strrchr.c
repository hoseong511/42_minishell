/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:55:23 by hossong           #+#    #+#             */
/*   Updated: 2021/11/25 12:08:43 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*start;

	start = s;
	while (*s != '\0')
		s++;
	while (s != start && *s != (char)c)
		s--;
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
