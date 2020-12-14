/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:22:20 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/22 20:30:38 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*destination;
	const char	*source;
	size_t		byte;

	if ((dst != src) && (n > 0))
	{
		destination = dst;
		source = src;
		if (destination < source)
			ft_memcpy(dst, src, n);
		else
		{
			byte = n;
			while (byte--)
			{
				destination[byte] = source[byte];
			}
		}
	}
	return (dst);
}
