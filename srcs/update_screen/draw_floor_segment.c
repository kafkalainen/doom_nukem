/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_segment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 09:29:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/21 16:54:34 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	draw_floor_strip(t_xy p0, t_xy p1, t_texture *tex, t_frame *frame)
{
	t_xy		delta;
	t_xy		pixel;
	t_xyz		corr_texel;
	t_xyz		texel;
	Uint32		colour;
	long int	pixels;

	(void)tex;
	delta.x = p1.x - p0.x;
	delta.y = p1.y - p0.y;
	pixels = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	delta.x /= pixels;
	delta.y /= pixels;
	pixel.x = p0.x;
	pixel.y = p0.y;
	texel = frame->ground_uv.top_left;
	corr_texel = texel;
	while (pixels)
	{
		corr_texel = inv_z(texel);
		colour = get_texel(corr_texel.x * (tex->w - 1),
		corr_texel.y * (tex->h - 1), tex);
		put_pixel(frame->buffer, (int)pixel.x, (int)pixel.y, colour);
		pixel.x += delta.x;
		pixel.y += delta.y;
		texel.x += frame->ground_uv_step_delta_u.x;
		texel.y += frame->ground_uv_step_delta_u.y;
		texel.z += frame->ground_uv_step_delta_u.z;
		texel.x += frame->ground_uv_step_delta_v.x;
		texel.y += frame->ground_uv_step_delta_v.y;
		texel.z += frame->ground_uv_step_delta_v.z;
		--pixels;
	}
}

static void	step_ground_one(t_frame *frame, t_plgn *box)
{
	// frame->ground_uv.top_left.x += 0.001;
	// frame->ground_uv.top_left.y += 0.001;
	// frame->ground_uv.top_left.z += frame->ground_uv_step_delta_x.z;
	(void)frame;
	box->bottom_left.y += 1;
	box->bottom_right.y += 1;
}

void	draw_linearly(t_frame *frame, t_texture *floor_tex, t_plgn *box)
{
	while (box->bottom_left.y < 0)
	{
		box->bottom_left.y++;
		box->bottom_right.y++;
	}
	while (box->bottom_right.y < SCREEN_HEIGHT
		|| box->bottom_left.y < SCREEN_HEIGHT)
	{
		draw_floor_strip(vec3_to_vec2(box->bottom_left),
			vec3_to_vec2(box->bottom_right), floor_tex, frame);
		step_ground_one(frame, box);
	}
}
