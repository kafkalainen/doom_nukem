/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:03:39 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/21 03:31:26 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned int	number;
	int				sign;

	if (str == 0 || *str == '\0')
		return (0);
	while (ft_isspace(*str))
		++str;
	sign = 1;
	while (*str == '-' || *str == '+')
	{
		sign = (*str == '-' ? -1 : 1);
		++str;
	}
	number = 0;
	while (ft_isdigit(*str))
	{
		number = (number * 10) + (*str - '0');
		++str;
	}
	return (sign * number);
}
