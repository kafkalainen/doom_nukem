/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:50:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/14 11:07:53 by jnivala          ###   ########.fr       */
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

static void	draw_vertical_floor_strip(t_xy offset, int height,
							t_texture *tex, t_frame *frame)
{
	int		cur_y;
	t_xyz	corr_texel;
	t_xyz	texel;
	Uint32	colour;

	texel = frame->ground_uv.top_left;
	corr_texel = texel;
	if (offset.x < 0 || offset.x > SCREEN_WIDTH)
		return ;
	cur_y = -1;
	while (cur_y < height)
	{
		corr_texel = inv_z(texel);
		if (cur_y + offset.y >= 0 && cur_y + offset.y < SCREEN_HEIGHT)
		{
			colour = get_texel(corr_texel.x * (tex->w - 1),
						corr_texel.y * (tex->h - 1), tex);
			put_pixel(frame->buffer, offset.x, cur_y + offset.y, colour);
		}
		cur_y++;
		texel.y += frame->ground_uv_step.y;
		texel.z += frame->ground_uv_step.z;
	}
}

static void	draw_vertical_ceiling_strip(t_xyz offset, int height,
							Uint32 colour, t_frame *frame)
{
	int	cur_y;

	if (offset.x < 0 || offset.x > SCREEN_WIDTH)
		return ;
	cur_y = -1;
	while (cur_y < height)
	{
		if (cur_y + offset.y >= 0 && cur_y + offset.y < SCREEN_HEIGHT)
			put_pixel(frame->buffer, offset.x,
				cur_y + offset.y,
				colour);
		cur_y++;
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

void	draw_vertically(t_frame *frame, t_sector *sector, t_texture *wall_tex)
{
	// Uint32		tex_floor;

	sector = sector;
	while (frame->outer_box.top_left.x + 1 < 0)
		step_one(frame);
	// tex_floor = get_floor(sector->tex_floor);
	while (frame->outer_box.top_left.x < frame->outer_box.top_right.x)
	{
		draw_vertical_ceiling_strip(
			vec3(frame->outer_box.top_left.x, 0, 0),
			frame->outer_box.top_left.y,
			green, frame);
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
		draw_vertical_floor_strip(
			vec3_to_vec2(frame->outer_box.bottom_left),
			SCREEN_HEIGHT - frame->outer_box.bottom_left.y, wall_tex, frame);
		step_one(frame);
	}
}

void	draw_segment(t_frame *frame, t_home *home, t_player *plr)
{
	t_texture	*wall_tex;

	// if (frame->left.wall->idx != -4)
	// 	return ;
	wall_tex = get_tex(-1, home->editor_tex);
	if (frame->left.wall->idx < 0)
		wall_tex = get_tex(frame->left.wall->idx, home->editor_tex);
	else
		wall_tex = get_tex(get_next_wall_tex(&frame->left.wall->next,
		home->sectors[frame->idx]->nb_of_walls), home->editor_tex);
	calc_dimensions(frame, plr, home);
	calc_wall_texels(frame, wall_tex->w);
	calc_ground_texels(home->sectors[frame->idx], frame, plr);
	if (plr->input.wireframe == 0)
		draw_vertically(frame, home->sectors[frame->idx], wall_tex);
	else
		draw_wireframe(frame, get_floor(home->sectors[frame->idx]->tex_floor));
}
