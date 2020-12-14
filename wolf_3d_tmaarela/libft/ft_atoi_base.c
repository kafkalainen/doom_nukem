/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 20:13:10 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/27 17:49:56 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** skip_prefix will determine which literal prefix a number string has, if any.
** They are: 0x111 (hex), 0b111 (bin), 0111 (oct)
*/

static int	skip_prefix(const char *str)
{
	size_t	length;
	int		bytes;

	length = ft_strlen(str);
	bytes = 0;
	if (length > 2 && str[0] == '0')
	{
		if (str[1] == 'x' || str[1] == 'b' || str[1] == 'X' || str[1] == 'B')
			bytes = 2;
	}
	else if (length > 1 && str[0] == '0')
	{
		bytes = 1;
	}
	return (bytes);
}

/*
** Takes a string and a [2,36] base and returns a 32bit value,
**	either [MIN_INT,MAX_INT] or [0,MAX_UINT]
**
** If no base is specified (0), the base will be determined
**	based on the literal prefix if one exists.
**	Otherwise base 10 is assumed.
**
** The literal prefix will always be skipped regardless of given base, but
**	if a nonsensical base is specified ("123", 2), the behavior is undefined.
*/

long		ft_atoi_base(const char *str, int base)
{
	long	number;

	if ((str == 0 || *str == '\0') || (base != 0 && (base < 2 || base > 36)))
		return (0);
	while (ft_isspace(*str))
		++str;
	if (base == 0)
		base = check_base_prefix(str);
	if (base == 10)
		return (ft_atoi(str));
	while (*str == '-' || *str == '+')
		++str;
	str += skip_prefix(str);
	number = 0;
	while (ft_isalnum(*str))
	{
		if (base < 10 || ft_isdigit(*str))
			number = (number * base) + (*str - '0');
		else
			number = (number * base) + (10 + ft_toupper(*str) - 'A');
		++str;
	}
	return (number);
}
