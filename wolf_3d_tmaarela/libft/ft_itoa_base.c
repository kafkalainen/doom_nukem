/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 13:36:21 by ngontjar          #+#    #+#             */
/*   Updated: 2020/08/16 04:23:06 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Handles everything except base-10
**	because of the negative sign.
*/

char	*ft_itoa_base(long long number, int base)
{
	char			string[64 + 1];
	long long		digits;
	unsigned int	index;
	unsigned int	mod;

	if (number == 0)
		return (ft_strdup("0"));
	if (base == 10)
		return (ft_itoa(number));
	base = ft_clamp(base, 2, 36);
	number = (number < 0) ? -number : number;
	digits = number;
	index = 0;
	while (digits)
		(++index) && (digits /= base);
	string[index] = '\0';
	while (~--index)
	{
		mod = number % base;
		string[index] = (mod < 10) ? ('0' + mod) : ('A' + (mod - 10));
		number /= base;
	}
	return (ft_strdup(string));
}
