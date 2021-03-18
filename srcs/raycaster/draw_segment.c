/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:50:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/18 12:37:42 by jnivala          ###   ########.fr       */
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

void			draw_floor_horizontally(t_frame *frame, t_texture *tex,
	t_home *home, t_player *plr)
{
	t_xyz		obj;
	float		y_min;
	t_xyz		floor_step;

	obj = (t_xyz){0.0f, 480.0f, 0.0f};
	y_min = ft_fmin(frame->bottom_left.y, frame->bottom_right.y);
	while (obj.y > y_min)
	{
		obj.x = frame->bottom_left.x;
		while (obj.x < frame->bottom_right.x)
		{
			put_pixel(frame->draw_surf, obj.x,
				obj.y, get_texel(1, 1, tex));
			obj.x++;
		}
		obj.y--;
	}
}


/*
**	Should the whole sector be drawn?
**	Use only horizontal drawing. 
**	What if scan_fov is flipped by 90 degrees?
**	Floor drawing must be done after scan_fov returns from the portal.
**	
**
*/
void			draw_segment(t_frame *frame, t_texture *tex,
							t_home *home, t_player *plr)
{
	// if (frame->left.wall->c != 'b')
	// 	return ;
	calc_distances(frame, tex, plr);
	calc_texels(frame, tex);
	draw_floor_horizontally(frame,
		get_tex(home->sectors[frame->idx]->tex_floor, home->editor_tex),
		home, plr);
	if (frame->left.wall->idx < 0)
		draw_wall_vertically(frame, tex, home, plr);
}
