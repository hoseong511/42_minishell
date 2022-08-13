/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:07:32 by hossong           #+#    #+#             */
/*   Updated: 2022/05/28 16:51:17 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_range(unsigned long long result, int sign)
{
	if (result > 9223372036854775807 && sign == -1)
		return (0);
	if (result > 9223372036854775807 && sign == 1)
		return (-1);
	return (result * sign);
}

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					np;

	np = 1;
	result = 0;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		np *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && ft_isdigit(*str))
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return (check_range(result, np));
}
