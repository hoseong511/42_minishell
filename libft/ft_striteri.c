/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:19:27 by hossong           #+#    #+#             */
/*   Updated: 2021/11/24 12:54:04 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	size_t			slen;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	slen = ft_strlen(s);
	while (i < slen)
	{
		f(i, s);
		i++;
		s++;
	}
}
