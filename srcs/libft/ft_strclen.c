/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 14:30:33 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/03 14:32:00 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

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
