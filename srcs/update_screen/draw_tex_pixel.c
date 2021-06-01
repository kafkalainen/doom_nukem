/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:22:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/01 08:54:14 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"


/*
**	Should we somehow eradicate modulo from getting the correct texel?
*/
Uint32	get_texel(int x, int y, t_texture *tex)
{
	// int	offset_x;
	// int	offset_y;

	// offset_x = x % tex->w;
	// offset_y = y % tex->h;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > tex->w)
		x = tex->w;
	if (y > tex->h)
		y = tex->h;
	return ((Uint32)tex->pixels[(y * tex->w) + x]);
}

void	draw_tex_pixel(t_texture *tex, t_xyz texel, t_xy pixel,
	t_frame *frame)
{
	Uint32		color;

	color = get_texel(texel.x * (tex->w - 1), texel.y * (tex->h - 1), tex);
	color = colour_scale(color, frame->left.wall->wall_facing);
	put_pixel(frame->buffer, pixel.x, pixel.y, color);
}
