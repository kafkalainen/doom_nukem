/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:50:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/28 14:47:31 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	draw_vertical_floor_strip(t_xyz offset, int height,
							Uint32 colour, t_frame *frame)
{
	int		cur_y;
	float	scale;
	float	step_z;

	if (offset.x < 0 || offset.x > SCREEN_WIDTH)
		return ;
	cur_y = -1;
	scale = (SCREEN_HEIGHT - offset.y) / (SCREEN_HEIGHT - frame->pitch);
	step_z = (1 - scale) / offset.y;
	scale = 0.3f;
	while (cur_y < height)
	{
		if (cur_y + offset.y >= 0 && cur_y + offset.y < SCREEN_HEIGHT)
			put_pixel(frame->buffer, offset.x,
				cur_y + offset.y,
				colour_scale(colour, scale));
		cur_y++;
		scale += step_z;
	}
}

static void	fit_to_screen_space(t_xy *offset, t_xyz *texel,
	size_t *height, float *uv_step_y)
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

static void	draw_vertical_wall_strip(t_xy offset, size_t height,
							t_texture *tex, t_frame *frame)
{
	size_t	cur_y;
	t_xyz	corr_texel;
	t_xyz	texel;
	Uint32	colour;

	cur_y = 0;
	texel = frame->uv.top_left;
	corr_texel = texel;
	fit_to_screen_space(&offset, &texel, &height, &frame->uv_step.y);
	while (cur_y < height)
	{
		if (cur_y % 16)
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

void	draw_vertically(t_frame *frame, t_sector *sector, t_texture *wall_tex,
		int wall)
{
	size_t		obj_x;
	t_xyz		start;
	t_xyz		end;
	t_xyz		bottom;
	Uint32		tex_floor;

	obj_x = 0;
	sector = sector;
	start = frame->box.top_left;
	end = frame->box.top_right;
	bottom = frame->box.bottom_left;
	while (obj_x + (start.x - 2) < 0)
		step_one(&start, &bottom, &obj_x, frame);
	tex_floor = get_floor(sector->tex_floor);
	while (obj_x + start.x < end.x)
	{
		if (wall)
			draw_vertical_wall_strip(
				vec2(start.x + obj_x, start.y), (bottom.y - start.y),
				wall_tex, frame);
		draw_vertical_floor_strip(
			vec3(start.x + obj_x, bottom.y, bottom.z),
			((SCREEN_HEIGHT - bottom.y) < 0 ? 0 : SCREEN_HEIGHT - bottom.y),
			tex_floor, frame);
		step_one(&start, &bottom, &obj_x, frame);
	}
}

void	draw_segment(t_frame *frame, t_home *home, t_player *plr, int wall)
{
	t_texture	*wall_tex;
	Uint32		colour;

	wall_tex = get_tex(-1, home->editor_tex);
	if (wall)
		wall_tex = get_tex(frame->left.wall->idx, home->editor_tex);
	calc_distances(frame, plr, &home->sectors[frame->idx]->ground,
		&home->sectors[frame->idx]->ceiling);
	calc_wall_texels(frame, wall_tex->w);
	if (plr->input.wireframe == 0)
		draw_vertically(frame, home->sectors[frame->idx], wall_tex, wall);
	else
	{
		colour = get_floor(home->sectors[frame->idx]->tex_floor);
		draw_line(vec3_to_vec2(frame->box.top_left),
			vec3_to_vec2(frame->box.top_right), colour, frame->buffer);
		draw_line(vec3_to_vec2(frame->box.bottom_left),
			vec3_to_vec2(frame->box.bottom_right), colour, frame->buffer);
		draw_line(vec3_to_vec2(frame->box.top_left),
			vec3_to_vec2(frame->box.bottom_left), colour, frame->buffer);
		draw_line(vec3_to_vec2(frame->box.top_right),
			vec3_to_vec2(frame->box.bottom_right), colour, frame->buffer);
	}
}
