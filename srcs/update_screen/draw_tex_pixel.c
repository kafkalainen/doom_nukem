/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:22:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/22 14:49:32 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_tex_pixel(t_texture *tex, t_xyz texel, t_xy pixel,
	t_frame *frame)
{
	Uint32		color;

	color = get_texel(texel.x * (tex->w - 1), texel.y * (tex->h - 1), tex);
	color = colour_scale(color, frame->left.wall->wall_facing);
	put_pixel(frame->buffer, pixel.x, pixel.y, color);
}
