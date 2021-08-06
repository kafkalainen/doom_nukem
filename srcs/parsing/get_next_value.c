/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 09:36:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/06 10:09:33 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	get_next_uint_value(Uint32 *nb, unsigned char *buf,
				unsigned int **pos, ssize_t size)
{
	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (1);
	*nb = (Uint32)ft_atoi((const char *)buf + **pos);
	return (0);
}

Uint32	get_next_int_value(int *nb, unsigned char *buf,
				unsigned int **pos, ssize_t size)
{
	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (1);
	*nb = ft_atoi((const char *)buf + **pos);
	return (0);
}

Uint32	get_next_float_value(float *nb, unsigned char *buf,
				unsigned int **pos, ssize_t size)
{
	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (1);
	*nb = (float)ft_atoi((const char *)buf + **pos);
	return (0);
}

Uint32	get_next_string(char **str, unsigned char *buf,
			unsigned int **pos, ssize_t size)
{
	ssize_t	len;

	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (1);
	len = get_next_breaker(buf + **pos);
	*str = ft_strndup((const char *)buf + **pos, len);
	return (0);
}
