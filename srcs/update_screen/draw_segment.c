/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:50:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/23 15:02:59 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// static void		draw_vertical_wall_strip(t_xy offset, size_t height,
// 							t_texture *tex, t_frame *frame)
// {
// 	size_t	cur_y;
// 	t_xyz	corr_texel;
// 	t_xyz	texel;
// 	int		i;

// 	if (offset.x < 0 || offset.x > SCREEN_WIDTH)
// 		return ;
// 	cur_y = 0;
// 	i = 0;
// 	texel = frame->uv_top_left;
// 	while (cur_y < height)
// 	{
// 		if (i++ % 16)
// 			corr_texel = inv_z(texel);
// 		if (cur_y + offset.y >= 0 && cur_y + offset.y < SCREEN_HEIGHT)
// 			put_pixel(frame->draw_surf, offset.x,
// 				cur_y + offset.y, get_texel(corr_texel.x * tex->w,
// 				corr_texel.y * tex->h, tex));
// 		cur_y++;
// 		texel.y += frame->uv_step.y;
// 	}
// }

// static void		draw_vertical_floor_strip(t_xyz offset, size_t height,
// 							t_texture *tex, t_frame *frame)
// {
// 	size_t	cur_y;
// 	t_xyz	corr_texel;
// 	t_xyz	texel;
// 	float	current_distance;
// 	float	weight;

// 	if (offset.x < 0 || offset.x > SCREEN_WIDTH)
// 		return ;
// 	cur_y = 0;
// 	texel = frame->ground_uv_t_l;
// 	while (cur_y < height)
// 	{
// 		// corr_texel = inv_z(texel);
// 		current_distance = SCREEN_HEIGHT / ((2.0f * (cur_y + offset.y + height)) - SCREEN_HEIGHT);
// 		weight = current_distance / offset.z;
// 		corr_texel.x = weight * texel.x + (1.0f - weight) * 320;
// 		corr_texel.y = weight * texel.y + (1.0f - weight) * 240;
// 		if (cur_y + offset.y >= 0 && cur_y + offset.y < SCREEN_HEIGHT)
// 			// put_pixel(frame->draw_surf, offset.x,
// 			// 	cur_y + offset.y, get_texel(corr_texel.x * tex->w,
// 			// 	corr_texel.y * tex->h, tex));
// 			put_pixel(frame->draw_surf, offset.x,
// 				cur_y + offset.y, get_texel(corr_texel.x * tex->w,
// 				corr_texel.y * tex->h, tex));
// 		cur_y++;
// 		texel.y += frame->ground_uv_step.y;
// 	}
// }

// void			draw_vertically(t_frame *frame, t_home *home, t_player *plr)
// {
// 	size_t		obj_x;
// 	t_xyz		start;
// 	t_xyz		end;
// 	t_xyz		bottom;
// 	t_texture	*wall_tex;
// 	// t_texture	*ground_tex;

// 	obj_x = 0;
// 	start = frame->top_left;
// 	end = frame->top_right;
// 	bottom = frame->bottom_left;
// 	wall_tex = get_tex(frame->left.wall->idx, home->editor_tex);
// 	// if (frame->left.wall->idx < 0)
// 	// else
// 	// 	wall_tex = get_tex(-3, home->editor_tex);
// 	// ground_tex = get_tex(home->sectors[frame->idx]->tex_floor, home->editor_tex);
// 	while (obj_x + start.x < end.x)
// 	{
// 		// if (frame->left.wall->idx < 0)
// 		// {
// 		draw_vertical_wall_strip(
// 			vec2(start.x + obj_x, start.y), (bottom.y - start.y),
// 			wall_tex, frame);
// 		// }
// 		// draw_vertical_floor_strip(
// 		// 	vec3(start.x + obj_x, bottom.y, bottom.z),
// 		// 	((SCREEN_HEIGHT - bottom.y) < 0 ? 0 : SCREEN_HEIGHT - bottom.y),
// 		// 	ground_tex,
// 		// 	frame);
// 		start.y = start.y - frame->step.y;
// 		bottom.y = bottom.y + frame->step.y;
// 		start.z = start.z - frame->step.z;
// 		frame->uv_top_left.x += frame->uv_step.x;
// 		frame->uv_top_left.z += frame->uv_step.z;
// 		// frame->ground_uv_t_l.x += frame->ground_uv_step.x;
// 		// frame->ground_uv_t_l.z += frame->ground_uv_step.z;
// 		obj_x++;
// 	}
// }

// void			draw_segment(t_frame *frame, t_home *home, t_player *plr)
// {
// 	// if (frame->left.wall->c != 'b')
// 	// 	return ;
// 	t_texture	*wall_tex;
// 	// if (frame->left.wall->idx < 0)
// 	wall_tex = get_tex(frame->left.wall->idx, home->editor_tex);
// 	// else
// 	// 	wall_tex = get_tex(-3, home->editor_tex);
// 	calc_distances(frame, wall_tex, plr);
// 	calc_wall_texels(frame, wall_tex);
// 	// calc_ground_texels(home->sectors[frame->idx], frame,
// 		// get_tex(home->sectors[frame->idx]->tex_floor, home->editor_tex));
// 	draw_vertically(frame, home, plr);
// }

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
				colour_scale(colour, scale > 1 ? 1 : scale));
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
	*height = *height > SCREEN_HEIGHT ? SCREEN_HEIGHT : *height;
}

static void	draw_vertical_wall_strip(t_xy offset, size_t height,
							t_texture *tex, t_frame *frame)
{
	size_t	cur_y;
	t_xyz	corr_texel;
	t_xyz	texel;
	Uint32	colour;

	cur_y = 0;
	texel = frame->uv_top_left;
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

void	draw_vertically(t_frame *frame, t_sector *sector,
	t_texture *wall_tex, int wall)
{
	size_t		obj_x;
	t_xyz		start;
	t_xyz		end;
	t_xyz		bottom;
	Uint32		tex_floor;

	obj_x = 0;
	start = frame->top_left;
	end = frame->top_right;
	bottom = frame->bottom_left;
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
	calc_distances(frame, plr);
	calc_wall_texels(frame, wall_tex->w);
	if (plr->input.wireframe == 1)
		draw_vertically(frame, home->sectors[frame->idx], wall_tex, wall);
	else
	{
		colour = get_floor(home->sectors[frame->idx]->tex_floor);
		draw_line(vec3_to_vec2(frame->top_left),
			vec3_to_vec2(frame->top_right), colour, frame->buffer);
		draw_line(vec3_to_vec2(frame->bottom_left),
			vec3_to_vec2(frame->bottom_right), colour, frame->buffer);
		draw_line(vec3_to_vec2(frame->top_left),
			vec3_to_vec2(frame->bottom_left), colour, frame->buffer);
		draw_line(vec3_to_vec2(frame->top_right),
			vec3_to_vec2(frame->bottom_right), colour, frame->buffer);
	}
}
