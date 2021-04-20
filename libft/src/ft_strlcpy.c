/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:06:00 by jnivala           #+#    #+#             */
/*   Updated: 2020/10/13 11:46:14 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		n;

	d = (char*)dst;
	s = (const char*)src;
	n = size;
	if (n != 0)
	{
		while (--n != 0 && *d != '\0' && *s != '\0')
		{
			*d = *s;
			d++;
			s++;
		}
	}
	if (n == 0)
	{
		if (size != 0)
			*d = '\0';
		while (*s)
			s++;
	}
	return (s - src);
}
