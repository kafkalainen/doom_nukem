/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:22:20 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/22 20:27:06 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*destination;
	const char	*source;
	size_t		byte;

	if (dst != src)
	{
		destination = dst;
		source = src;
		byte = 0;
		while (byte < n)
		{
			destination[byte] = source[byte];
			++byte;
		}
	}
	return (dst);
}
