/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:33:01 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/25 11:33:01 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

int		ft_atoi(const char *str)
{
	unsigned int	number;
	int				sign;

	if (str == 0 || *str == '\0')
		return (0);
	while (*str == ' '|| *str == '\t')
		++str;
	sign = 1;
	while (*str == '-' || *str == '+')
	{
		sign = (*str == '-' ? -1 : 1);
		++str;
	}
	number = 0;
	while (*str >= '0' && *str <= '9')
	{
		number = (number * 10) + (*str - '0');
		++str;
	}
	return (sign * number);
}
