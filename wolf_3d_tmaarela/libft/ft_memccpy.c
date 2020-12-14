/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:43:06 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/22 20:28:56 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*destination;
	const unsigned char	*source;
	size_t				byte;

	destination = dst;
	source = src;
	byte = 0;
	while (byte < n)
	{
		destination[byte] = source[byte];
		if (source[byte] == (unsigned char)c)
		{
			return (destination + byte + 1);
		}
		++byte;
	}
	return (NULL);
}
