/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:50:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/04 10:12:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**		Line 31 nulling:
**		might be inefficient
*/
void	*optimized_memcpy(void *pixels, void *src, size_t size)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	s = (char *)src;
	d = (char *)pixels;
	while (i < size)
	{
		d[i] = s[i];
		s[i] = 0;
		i++;
	}
	return (d);
}

/*
** 1st pass at loading char* and converting back to t_texture.
** Need to see text output before making further changes
*/
void	free_array(unsigned char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_strdel((char **)&array[i]);
		i++;
	}
	free(array);
}
