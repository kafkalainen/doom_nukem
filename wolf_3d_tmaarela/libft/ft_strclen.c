/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:24:44 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/04 16:35:14 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function is similar to strlen,
** except it counts length until the specified character
** or terminating character is found.
*/

size_t	ft_strclen(const char *str, int c)
{
	size_t length;

	length = 0;
	c = (unsigned char)c;
	if (str != NULL)
	{
		while (*str != c)
		{
			++length;
			++str;
		}
	}
	return (length);
}
