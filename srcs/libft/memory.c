/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:52:55 by tmaarela          #+#    #+#             */
/*   Updated: 2020/12/14 13:52:55 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

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

void	ft_memdel(void **p)
{
	if (*p != NULL)
	{
		free(*p);
		*p = NULL;
	}
}
