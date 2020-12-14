/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 02:59:17 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/20 04:17:18 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Intended for 32bit input ranges [MIN_INT, MAX_UINT]
** -2147483648, 2147483647, 4294967295
*/

int		ft_numlen_base(long number, int base)
{
	int length;

	if (number == 0)
		return (1);
	if (base < 2)
		return (0);
	if (base == 10)
		return (ft_numlen(number));
	number = (unsigned int)number;
	length = 0;
	while (number)
	{
		++length;
		number /= base;
	}
	return (length);
}
