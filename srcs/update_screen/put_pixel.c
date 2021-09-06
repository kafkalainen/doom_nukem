/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:34:26 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/06 16:11:27 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xy	scale(t_xy a)
{
	return (vec2(a.x * MINIMAP_SIZE, a.y * MINIMAP_SIZE));
}

void	put_pixel(t_buffer *buffer, t_pxl_coords xy, Uint32 color)
{
	Uint8	alpha;

	alpha = (color & 0xFF000000) >> 24;
	if (xy.x > buffer->width - 1 || xy.y > buffer->height - 1
		|| xy.x < 0 || xy.y < 0 || alpha < 50)
		return ;
	*(buffer->pxl_buffer + (buffer->width * xy.y) + xy.x) = color;
}
