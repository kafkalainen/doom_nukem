/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall_texels.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:50:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/03 12:42:33 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	set_no_offset(t_frame *frame)
{
	frame->middle_uv.top_left = inv_z((t_xyz){0.0f, 0.0f,
			frame->outer_box.top_left.z});
	frame->middle_uv.bottom_left = inv_z((t_xyz){0.0f, 1.0f,
			frame->outer_box.bottom_left.z});
	frame->middle_uv.top_right = inv_z((t_xyz){frame->ratio * frame->tex_mult,
			0.0f, frame->outer_box.top_right.z});
	frame->middle_uv.bottom_right = inv_z((t_xyz){frame->ratio
			* frame->tex_mult, 1.0f, frame->outer_box.bottom_right.z});
}

static void	set_offset_from_both_ends(t_frame *frame)
{
	frame->middle_uv.top_left = inv_z((t_xyz){frame->unvisible_l_side
			* frame->tex_mult, 0.0f, frame->outer_box.top_left.z});
	frame->middle_uv.bottom_left = inv_z((t_xyz){frame->unvisible_l_side
			* frame->tex_mult, 1.0f, frame->outer_box.bottom_left.z});
	frame->middle_uv.top_right = inv_z((t_xyz){(frame->unvisible_l_side
				+ frame->ratio)
			* frame->tex_mult, 0.0f, frame->outer_box.top_right.z});
	frame->middle_uv.bottom_right = inv_z((t_xyz){(frame->unvisible_l_side
				+ frame->ratio)
			* frame->tex_mult, 1.0f, frame->outer_box.bottom_right.z});
}

static void	set_offset_from_left_side(t_frame *frame)
{
	frame->middle_uv.top_left = inv_z((t_xyz){frame->unvisible_l_side
			* frame->tex_mult, 0.0f, frame->outer_box.top_left.z});
	frame->middle_uv.bottom_left = inv_z((t_xyz){frame->unvisible_l_side
			* frame->tex_mult, 1.0f, frame->outer_box.bottom_left.z});
	frame->middle_uv.top_right = inv_z((t_xyz){frame->tex_mult, 0.0f,
			frame->outer_box.top_right.z});
	frame->middle_uv.bottom_right = inv_z((t_xyz){frame->tex_mult, 1.0f,
			frame->outer_box.bottom_right.z});
}

static void	calc_offsets(t_frame *frame)
{
	if (frame->left.wall->x0.x == frame->left.l_pt.x
		&& frame->left.wall->x0.y == frame->left.l_pt.y)
		set_no_offset(frame);
	else if (frame->left.wall == frame->right.wall)
		set_offset_from_both_ends(frame);
	else
		set_offset_from_left_side(frame);
}

void	calc_wall_texels(t_frame *frame, int tex_width)
{
	frame->visible_wall_dist = vec2_eucl_dist(frame->left.l_pt,
			frame->left.r_pt);
	frame->full_wall_dist = vec2_eucl_dist(frame->left.wall->x0,
			frame->left.wall->next->x0);
	frame->ratio = frame->visible_wall_dist / frame->full_wall_dist;
	frame->tex_mult = frame->full_wall_dist / tex_width;
	frame->unvisible_l_side = vec2_eucl_dist(frame->left.wall->x0,
			frame->left.l_pt) / frame->full_wall_dist;
	calc_offsets(frame);
	frame->uv_step.x = interpolate_points(frame->middle_uv.top_left.x,
			frame->middle_uv.top_right.x, frame->outer_box.top_left.x,
			frame->outer_box.top_right.x);
	frame->uv_step.y = interpolate_points(frame->middle_uv.top_left.y,
			frame->middle_uv.bottom_left.y, frame->outer_box.top_left.y,
			frame->outer_box.bottom_left.y);
	frame->uv_step.z = interpolate_points(frame->middle_uv.top_left.z,
			frame->middle_uv.top_right.z, frame->outer_box.top_left.x,
			frame->outer_box.top_right.x);
}
