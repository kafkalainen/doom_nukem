/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:50:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/19 11:16:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

static void		draw_vertical_wall_strip(t_xy offset, size_t height,
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

static void		draw_vertical_floor_strip(t_xyz offset, size_t height,
							t_texture *tex, t_frame *frame)
{
	size_t	cur_y;
	t_xyz	corr_texel;
	t_xyz	texel;
	float	current_distance;
	float	weight;

	if (offset.x < 0 || offset.x > SCREEN_WIDTH)
		return ;
	cur_y = 0;
	texel = frame->uv_top_left;
	while (cur_y < height)
	{
		current_distance = SCREEN_HEIGHT / ((2.0f * (cur_y + offset.y + height)) - SCREEN_HEIGHT) / SQR2;
		weight = current_distance / offset.z;
		corr_texel.x = weight * offset.x + (1.0f - weight) * 320;
		corr_texel.y = weight * offset.y + (1.0f - weight) * 240;
		if (cur_y + offset.y >= 0 && cur_y + offset.y < SCREEN_HEIGHT)
			put_pixel(frame->draw_surf, offset.x,
				cur_y + offset.y, get_texel(corr_texel.x * tex->w,
				corr_texel.y * tex->h, tex));
		cur_y++;
		texel.y += frame->uv_step.y;
	}
}

void			draw_vertically(t_frame *frame, t_home *home, t_player *plr)
{
	size_t		obj_x;
	t_xyz		start;
	t_xyz		end;
	t_xyz		bottom;
	t_texture	*ground_tex;
	t_texture	*wall_tex;

	obj_x = 0;
	start = frame->top_left;
	end = frame->top_right;
	bottom = frame->bottom_left;
	if (frame->left.wall->idx < 0)
		wall_tex = get_tex(frame->left.wall->idx, home->editor_tex);
	else
		wall_tex = get_tex(-3, home->editor_tex);
	ground_tex = get_tex(home->sectors[frame->idx]->tex_floor, home->editor_tex);
	while (obj_x + start.x < end.x)
	{
		if (frame->left.wall->idx < 0)
		{
			draw_vertical_wall_strip(
				vec2(start.x + obj_x, start.y), (bottom.y - start.y),
				wall_tex, frame);
		}
		draw_vertical_floor_strip(
			vec3(start.x + obj_x, bottom.y, bottom.z),
			((SCREEN_HEIGHT - bottom.y) < 0 ? 0 : SCREEN_HEIGHT - bottom.y),
			ground_tex,
			frame);
		start.y = start.y - frame->step.y;
		bottom.y = bottom.y + frame->step.y;
		start.z = start.z - frame->step.z;
		frame->uv_top_left.x += frame->uv_step.x;
		frame->uv_top_left.z += frame->uv_step.z;
		obj_x++;
	}
}

/*
**	Should the whole sector be drawn?
**	Floor texture mapping is done to the whole sector.
**	Use only horizontal drawing.
**	What if scan_fov is flipped by 90 degrees?
**	Floor drawing must be done after scan_fov returns from the portal.
**	Start by streching the floor tile across the entire sector.
**	Floor tiles are handled as vertical objects
**	Plr->pos and plr->dir are accummulated values, and only applied to the coordinates when calculating world points.
*/
void			draw_segment(t_frame *frame, t_home *home, t_player *plr)
{
	// if (frame->left.wall->c != 'b')
	// 	return ;
	t_texture	*wall_tex;
	if (frame->left.wall->idx < 0)
		wall_tex = get_tex(frame->left.wall->idx, home->editor_tex);
	else
		wall_tex = get_tex(-3, home->editor_tex);
	calc_distances(frame, wall_tex, plr);
	calc_wall_texels(frame, wall_tex);
	draw_vertically(frame, home, plr);
	// draw_floor_vertically(frame, tex, home, plr);

}
