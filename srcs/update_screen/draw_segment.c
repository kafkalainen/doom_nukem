/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:50:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/20 13:01:22 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	fit_to_screen_space(t_xy *offset, t_xyz *texel,
	int *height, float *uv_step_y)
{
	if (offset->y < 0)
	{
		texel->y += *uv_step_y * -offset->y;
		*height += offset->y;
		offset->y = 0;
	}
	if (*height > SCREEN_HEIGHT)
		*height = SCREEN_HEIGHT;
}

static void	draw_vertical_wall_strip(t_xy offset, int height,
							t_texture *tex, t_frame *frame)
{
	int				cur_y;
	t_xyz			corr_texel;
	t_pxl_coords	c;
	t_xyz			texel;
	Uint32			colour;

	cur_y = 0;
	texel = frame->middle_uv.top_left;
	corr_texel = texel;
	fit_to_screen_space(&offset, &texel, &height, &frame->uv_step.y);
	while (cur_y < height)
	{
		corr_texel = inv_z(texel);
		if (cur_y + offset.y >= 0 && cur_y + offset.y < SCREEN_HEIGHT)
		{
			c.x = offset.x;
			c.y = cur_y + offset.y;
			colour = colour_scale(get_texel(corr_texel.x * (tex->w - 1),
						corr_texel.y * (tex->h - 1), tex),
					frame->left.wall->wall_facing);
			put_pixel(&frame->buffer, c, colour);
		}
		cur_y++;
		texel.y += frame->uv_step.y;
	}
}

void	draw_vertically(t_frame *frame, t_texture *wall_tex)
{
	while (frame->outer_box.top_left.x + 1 < 0)
		step_one(frame);
	while (frame->outer_box.top_left.x < frame->outer_box.top_right.x)
	{
		if (frame->draw_top)
			draw_vertical_wall_strip(
				vec3_to_vec2(frame->outer_box.top_left),
				(frame->inner_box.top_left.y - frame->outer_box.top_left.y),
				wall_tex, frame);
		if (frame->draw_middle)
			draw_vertical_wall_strip(
				vec3_to_vec2(frame->outer_box.top_left),
				(frame->outer_box.bottom_left.y - frame->outer_box.top_left.y),
				wall_tex, frame);
		if (frame->draw_bottom)
			draw_vertical_wall_strip(
				vec3_to_vec2(frame->inner_box.bottom_left),
				(frame->outer_box.bottom_left.y
					- frame->inner_box.bottom_left.y), wall_tex, frame);
		step_one(frame);
	}
}

void	draw_segment(t_frame *frame, t_sector **sectors, t_texture **textures, t_player *plr)
{
	t_texture	*wall_tex;

	wall_tex = get_tex(-1, textures);
	if (frame->left.wall->idx < 0)
		wall_tex = get_tex(frame->left.wall->idx, textures);
	else
		wall_tex = get_tex(get_next_wall_tex(&frame->left.wall->next,
					sectors[frame->idx]->nb_of_walls), textures);
	calc_wall_dimensions(frame, plr, sectors);
	calc_wall_texels(frame, wall_tex->w);
	if (plr->input.wireframe == 0)
		draw_vertically(frame, wall_tex);
	else
		draw_wireframe(frame, get_floor(sectors[frame->idx]->tex_floor));
}
