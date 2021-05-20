/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:50:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/20 15:09:31 by jnivala          ###   ########.fr       */
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

void	draw_floor_strip(t_xy p0, t_xy p1, t_texture *tex, t_frame *frame)
{
	t_xy		delta;
	t_xy		pixel;
	long int	pixels;
	t_xyz		corr_texel;
	t_xyz		texel;
	Uint32		colour;

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
		texel.x += frame->ground_uv_step.x;
		--pixels;
	}
}

static void	draw_vertical_wall_strip(t_xy offset, int height,
							t_texture *tex, t_frame *frame)
{
	int		cur_y;
	t_xyz	corr_texel;
	t_xyz	texel;
	Uint32	colour;

	cur_y = 0;
	texel = frame->middle_uv.top_left;
	corr_texel = texel;
	fit_to_screen_space(&offset, &texel, &height, &frame->uv_step.y);
	while (cur_y < height)
	{
		corr_texel = inv_z(texel);
		if (cur_y + offset.y >= 0 && cur_y + offset.y < SCREEN_HEIGHT)
		{
			colour = colour_scale(get_texel(corr_texel.x * (tex->w - 1),
						corr_texel.y * (tex->h - 1), tex),
					frame->left.wall->wall_facing);
			put_pixel(frame->buffer, offset.x, cur_y + offset.y, colour);
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

static void	step_ground_one(t_frame *frame, t_plgn *box)
{
	// (void)frame;
	frame->ground_uv.top_left.y += frame->ground_uv_step.y;
	frame->ground_uv.top_left.z += frame->ground_uv_step.z;
	box->bottom_left.y += 1;
	box->bottom_right.y += 1;
}

void	draw_linearly(t_frame *frame, t_texture *floor_tex, t_plgn *box)
{
	while (box->bottom_right.y < 0)
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

void	draw_segment(t_frame *frame, t_home *home, t_player *plr)
{
	t_texture	*wall_tex;
	t_texture	*floor_tex;
	t_plgn		box;

	wall_tex = get_tex(-1, home->editor_tex);
	floor_tex = get_tex(-2, home->editor_tex);
	if (frame->left.wall->idx < 0)
		wall_tex = get_tex(frame->left.wall->idx, home->editor_tex);
	else
		wall_tex = get_tex(get_next_wall_tex(&frame->left.wall->next,
					home->sectors[frame->idx]->nb_of_walls), home->editor_tex);
	calc_wall_dimensions(frame, plr, home);
	calc_wall_texels(frame, wall_tex->w);
	calc_ground_texels(home->sectors[frame->idx], frame, plr);
	box = frame->outer_box;
	if (plr->input.wireframe == 0)
	{
		draw_vertically(frame, wall_tex);
		draw_linearly(frame, floor_tex, &box);
	}
	else
		draw_wireframe(frame, get_floor(home->sectors[frame->idx]->tex_floor));
}
