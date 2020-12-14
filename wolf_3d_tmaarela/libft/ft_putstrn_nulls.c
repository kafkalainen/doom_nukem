/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrn_nulls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:39:57 by ngontjar          #+#    #+#             */
/*   Updated: 2020/07/26 04:46:23 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function is similar to ft_pustrn,
** except each non-printing character (including NULL) is replaced
** by the specified character, preferably one that
** should not be encountered in n bytes.
*/

size_t	ft_putstrn_nulls(const char *str, const char c, size_t n)
{
	size_t		byte;

	byte = 0;
	if (str != NULL)
	{
		while (byte < n)
		{
			if (!ft_isprint(str[byte]))
				write(1, &c, 1);
			else
				write(1, &str[byte], 1);
			++byte;
		}
	}
	return (byte);
}
