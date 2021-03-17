/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_texels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 10:50:18 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/17 16:12:33 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

static void		calc_offsets(t_frame *frame)
{
	if (frame->left.wall->x0.x == frame->left.l_pt.x
		&& frame->left.wall->x0.y == frame->left.l_pt.y)
	{
		frame->uv_top_left = inv_z((t_xyz){0.0f, 0.0f, frame->top_left.z});
		frame->uv_bottom_left = inv_z((t_xyz){0.0f, 1.0f,
			frame->bottom_left.z});
		frame->uv_top_right = inv_z((t_xyz){frame->ratio * frame->tex_mult,
			0.0f, frame->top_right.z});
		frame->uv_bottom_right = inv_z((t_xyz){frame->ratio * frame->tex_mult,
			1.0f, frame->bottom_right.z});
	}
	else if (frame->left.wall == frame->right.wall)
	{
		frame->uv_top_left = inv_z((t_xyz){frame->unvisible_l_side
			* frame->tex_mult, 0.0f, frame->top_left.z});
		frame->uv_bottom_left = inv_z((t_xyz){frame->unvisible_l_side
			* frame->tex_mult, 1.0f, frame->bottom_left.z});
		frame->uv_top_right = inv_z((t_xyz){(frame->unvisible_l_side
			+ frame->ratio) * frame->tex_mult, 0.0f, frame->top_right.z});
		frame->uv_bottom_right = inv_z((t_xyz){(frame->unvisible_l_side
			+ frame->ratio) * frame->tex_mult, 1.0f, frame->bottom_right.z});
	}
	else
	{
		frame->uv_top_left = inv_z((t_xyz){frame->unvisible_l_side
			* frame->tex_mult, 0.0f, frame->top_left.z});
		frame->uv_bottom_left = inv_z((t_xyz){frame->unvisible_l_side
			* frame->tex_mult, 1.0f, frame->bottom_left.z});
		frame->uv_top_right = inv_z((t_xyz){frame->tex_mult, 0.0f,
			frame->top_right.z});
		frame->uv_bottom_right = inv_z((t_xyz){frame->tex_mult, 1.0f,
			frame->bottom_right.z});
	}
}

void			calc_texels(t_frame *frame, t_texture *tex)
{
	frame->visible_wall_dist = get_distance(frame->left.l_pt, frame->left.r_pt);
	frame->full_wall_dist = get_distance(frame->left.wall->x0,
		frame->left.wall->next->x0);
	frame->screen_wall_len = frame->top_right.x - frame->top_left.x;
	frame->ratio = frame->visible_wall_dist / frame->full_wall_dist;
	frame->tex_mult = frame->full_wall_dist / tex->w;
	frame->unvisible_l_side = get_distance(frame->left.wall->x0,
		frame->left.l_pt) / frame->full_wall_dist;
	frame->unvisible_r_side = get_distance(frame->left.wall->next->x0,
		frame->left.r_pt) / frame->full_wall_dist;
	calc_offsets(frame);
	frame->uv_step.x = interpolate_points(frame->uv_top_left.x,
		frame->uv_top_right.x, frame->top_left.x, frame->top_right.x);
	frame->uv_step.y = interpolate_points(frame->uv_top_left.y,
		frame->uv_bottom_left.y, frame->top_left.y, frame->bottom_left.y);
	frame->uv_step.z = interpolate_points(frame->uv_top_left.z,
		frame->uv_top_right.z, frame->top_left.x, frame->top_right.x);
}
