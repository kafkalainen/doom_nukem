/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 05:35:20 by ngontjar          #+#    #+#             */
/*   Updated: 2020/07/25 08:19:20 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long double	g_round[] =
{
	0.5,
	0.05,
	0.005,
	0.0005,
	0.00005,
	0.000005,
	0.0000005,
	0.00000005,
	0.000000005,
	0.0000000005,
	0.00000000005,
	0.000000000005,
	0.0000000000005,
	0.00000000000005,
	0.000000000000005,
	0.0000000000000005,
	0.00000000000000005,
	0.000000000000000005,
	0.0000000000000000005,
	0.00000000000000000005,
};

static void			buf_integer(
					char *buffer,
					unsigned long integer,
					unsigned char sign,
					unsigned char *i)
{
	unsigned char length;

	length = ft_numlen_ul(integer);
	while (length--)
	{
		buffer[sign + length] = '0' + (integer % 10);
		integer /= 10;
		++(*i);
	}
}

static void			buf_fractional(
					char *buffer,
					long double floating,
					unsigned char precision,
					unsigned char *i)
{
	if (precision)
	{
		buffer[(*i)++] = '.';
		while (precision--)
		{
			floating *= 10;
			buffer[(*i)++] = '0' + (int)floating;
			floating -= (int)floating;
		}
	}
}

static char			*check_invalid(long double floating)
{
	if (floating != floating)
		return (ft_strdup("nan"));
	else if (floating == INFINITY)
		return (ft_strdup("inf"));
	else if (floating == -INFINITY)
		return (ft_strdup("-inf"));
	else
		return (NULL);
}

/*
** At least 16 digits of precision.
*/

char				*ft_ftoa(long double floating, unsigned char precision)
{
	char			buffer[128];
	unsigned char	i;
	unsigned long	integer;
	unsigned char	sign;
	char			*error;

	if ((error = check_invalid(floating)))
		return (error);
	i = 0;
	precision = (19 < precision) ? 19 : precision;
	if ((sign = (signbit(floating) != 0)))
	{
		floating = -floating;
		buffer[i++] = '-';
	}
	floating += g_round[precision];
	integer = (unsigned long)floating;
	floating -= integer;
	buf_integer(buffer, integer, sign, &i);
	buf_fractional(buffer, floating, precision, &i);
	buffer[i++] = '\0';
	return (ft_strdup(buffer));
}
