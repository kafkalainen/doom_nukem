/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:18:20 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/22 18:05:51 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t n)
{
	char	*pointer;
	size_t	byte;

	c = (unsigned char)c;
	pointer = dst;
	byte = 0;
	while (byte < n)
	{
		pointer[byte] = c;
		++byte;
	}
	return (dst);
}
