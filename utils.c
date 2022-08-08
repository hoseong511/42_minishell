/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:58:09 by hossong           #+#    #+#             */
/*   Updated: 2022/08/07 17:08:26 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_strstr(char *str, char *to_find)
{
	if (!(*to_find))
		return (str);
	while (*str)
	{
		if (ft_strchr(to_find, *str) != 0)
			return (str);
		str++;
	}
	return (0);
}
