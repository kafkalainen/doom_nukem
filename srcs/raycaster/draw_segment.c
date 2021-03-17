/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:50:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/17 16:07:02 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

static void		draw_vertical_line(t_xy offset, size_t height,
							t_texture *tex, t_frame *frame)
{
	size_t	cur_y;
	t_xyz	corr_texel;
	t_xyz	texel;

	if (offset.x < 0 || offset.x > SCREEN_WIDTH)
		return ;
	cur_y = 0;
	texel = frame->uv_top_left;
	while (cur_y < height)
	{
		corr_texel = inv_z(texel);
		if (cur_y + offset.y >= 0 && cur_y + offset.y < SCREEN_HEIGHT)
			put_pixel(frame->draw_surf, offset.x,
				cur_y + offset.y, get_texel(corr_texel.x * tex->w,
				corr_texel.y * tex->h, tex));
		cur_y++;
		texel.y += frame->uv_step.y;
	}
}

void			draw_wall_vertically(t_frame *frame, t_texture *tex,
	t_home *home, t_player *plr)
{
	size_t		obj_x;

	obj_x = 0;
	while (obj_x + frame->top_left.x < frame->top_right.x)
	{
		draw_vertical_line(
			vec2(frame->top_left.x + obj_x, frame->top_left.y),
			(frame->bottom_left.y - frame->top_left.y),
			tex,
			frame);
		frame->top_left.y = frame->top_left.y - frame->step.y;
		frame->bottom_left.y = frame->bottom_left.y + frame->step.y;
		frame->top_left.z = frame->top_left.z - frame->step.z;
		frame->uv_top_left.x += frame->uv_step.x;
		frame->uv_top_left.z += frame->uv_step.z;
		obj_x++;
	}
}

void			draw_ceil_horizontally(t_frame *frame, t_texture *tex,
	t_home *home, t_player *plr)
{
	t_xyz		obj;

	obj = (t_xyz){0.0f, 0.0f, 0.0f};
	while (obj.z < frame->top_right.z)
	{
		frame->top_left.y = frame->top_left.y - frame->step.y;
		frame->top_left.z = frame->top_left.z - frame->step.z;
		frame->uv_top_left.x += frame->uv_step.x;
		frame->uv_top_left.z += frame->uv_step.z;
		obj.z += frame->uv_step.z;
	}
}

void			draw_segment(t_frame *frame, t_texture *tex,
							t_home *home, t_player *plr)
{
	calc_distances(frame, tex, plr);
	calc_texels(frame, tex);
	draw_wall_vertically(frame, tex, home, plr);
}
