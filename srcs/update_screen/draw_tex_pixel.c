/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:22:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/21 17:23:36 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_tex_pixel(t_texture *tex, t_xyz texel, t_xy pixel,
	t_frame *frame)
{
	Uint32		color;

	color = get_texel(texel.x * (tex->w - 1), texel.y * (tex->h - 1), tex);
	color = colour_scale(color, frame->left.wall->wall_facing);
	put_pixel(frame->draw_surf, pixel.x, pixel.y, color);
}
