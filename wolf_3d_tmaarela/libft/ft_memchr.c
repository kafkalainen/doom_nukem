/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:52:30 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/22 20:32:01 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	const char	*source;
	size_t		byte;

	source = src;
	byte = 0;
	while (byte < n)
	{
		if (source[byte] == c)
		{
			return ((void *)&source[byte]);
		}
		++byte;
	}
	return (NULL);
}
