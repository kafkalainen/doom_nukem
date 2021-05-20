/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 15:43:24 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/20 12:22:14 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	fit_to_screen_space_x(t_xy *offset, t_xyz *texel,
	int *height, float *uv_step_y)
{
	(void)uv_step_y;
	(void)texel;
	if (offset->x < 0)
	{
		// texel->y += *uv_step_y * -offset->y;
		*height += offset->x;
		offset->x = 0;
	}
	if (*height > SCREEN_WIDTH)
		*height = SCREEN_WIDTH;
}

static void	draw_horizontal_floor_strip(t_xy offset, int width,
							t_texture *tex, t_frame *frame)
{
	int		cur_x;
	// t_xyz	corr_texel;
	t_xyz	texel;
	// Uint32	colour;

	cur_x = 0;
	(void)tex;
	// texel = frame->middle_uv.top_left;
	// corr_texel = texel;
	fit_to_screen_space_x(&offset, &texel, &width, &frame->ground_uv_step.x);
	while (cur_x < width)
	{
		// corr_texel = inv_z(texel);
		// if (cur_y + offset.y >= 0 && cur_y + offset.y < SCREEN_HEIGHT)
		// {
		// 	colour = colour_scale(get_texel(corr_texel.x * (tex->w - 1),
		// 				corr_texel.y * (tex->h - 1), tex),
		// 			frame->left.wall->wall_facing);
			put_pixel(frame->buffer, cur_x + offset.x, offset.y, blueviolet);
		// }
		cur_x++;
		// texel.y += frame->ground_uv_step.y;
	}
}

static void	step_ground_one(t_frame *frame)
{
	frame->inner_box.top_left.x -= frame->step_ground_left_top.x;
	frame->ground_uv.top_left.y += frame->ground_uv_step.y;
	frame->inner_box.top_right.x += frame->step_ground_right_top.x;
	// frame->outer_box.top_left.y -= frame->step_outer_top.y;
	// frame->outer_box.top_left.z -= frame->step_outer_top.z;
	// frame->outer_box.bottom_left.y -= frame->step_outer_bot.y;
	// frame->outer_box.top_left.x += 1;
	// frame->outer_box.bottom_left.x += 1;
	frame->inner_box.top_left.y += 1;
	frame->inner_box.top_right.y += 1;
}

static void	draw_ground_horizontally(t_frame *frame, t_texture *ground_tex)
{
	while (frame->inner_box.top_left.y + 1 < 0)
		step_ground_one(frame);
	while (frame->inner_box.top_left.y < frame->inner_box.bottom_right.y)
	{
		if (frame->draw_ground)
			draw_horizontal_floor_strip(
				vec3_to_vec2(frame->inner_box.top_left),
				(frame->inner_box.top_right.x - frame->inner_box.top_left.x),
				ground_tex, frame);
		step_ground_one(frame);
	}
}

void	draw_sector(t_frame *frame, t_home *home, t_player *plr)
{
	t_texture	*ground_tex;

	ground_tex = get_tex(home->sectors[frame->idx]->tex_floor, home->editor_tex);
	calc_ground_dimensions(frame, plr, home);
	calc_ground_texels(home->sectors[frame->idx], frame, plr);
	draw_ground_horizontally(frame, ground_tex);
}
