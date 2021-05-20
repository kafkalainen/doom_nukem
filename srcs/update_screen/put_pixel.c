/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:34:26 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/20 12:09:17 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xy	scale(t_xy a)
{
	return (vec2(a.x * MINIMAP_SIZE, a.y * MINIMAP_SIZE));
}

void	put_pixel(t_buffer *buffer, t_pxl_coords xy, Uint32 color)
{
	if (xy.x > buffer->width - 1 || xy.y > buffer->height - 1 || xy.x < 0 || xy.y < 0)
		return ;
	buffer->pxl_buffer[(buffer->width * xy.y) + xy.x] = color;
}
