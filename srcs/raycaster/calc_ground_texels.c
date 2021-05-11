/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ground_texels.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:54:25 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/11 10:32:37 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static float	vec2_dist_from_point(t_xy *x1, t_xy *x2, t_xy *x0)
{
	return (fabsf(((x2->x - x1->x) * (x1->y - x0->y) - (x1->x - x0->x) * (x2->y - x1->y)))
	/ vec2_eucl_dist(*x1, *x2));
}

static void	calc_offsets(t_sector *sector, t_frame *frame)
{
	frame->ground_uv.bottom_left.x = vec2_dist_from_point(&sector->floor_top_right,
		&sector->floor_bottom_right, &(t_xy){0, 0})
		/ vec2_eucl_dist(sector->floor_top_right, sector->floor_top_left);
	frame->ground_uv.bottom_left.y = vec2_dist_from_point(&sector->floor_bottom_left,
		&sector->floor_bottom_right, &(t_xy){0, 0})
		/ vec2_eucl_dist(sector->floor_bottom_left, sector->floor_top_left);
	frame->ground_uv.top_left.x = vec2_dist_from_point(&sector->floor_top_right,
		&sector->floor_bottom_right, &frame->left.l_pt)
		/ vec2_eucl_dist(sector->floor_top_right, sector->floor_top_left);
	frame->ground_uv.top_left.y = vec2_dist_from_point(&sector->floor_bottom_left,
		&sector->floor_bottom_right, &frame->left.l_pt)
		/ vec2_eucl_dist(sector->floor_bottom_left, sector->floor_top_left);
	frame->ground_uv.top_left.z = frame->outer_box.bottom_left.z;
	frame->ground_uv.top_right.x = vec2_dist_from_point(&sector->floor_top_right,
		&sector->floor_bottom_right, &frame->left.r_pt)
		/ vec2_eucl_dist(sector->floor_top_right, sector->floor_top_left);
	frame->ground_uv.top_right.y = vec2_dist_from_point(&sector->floor_bottom_left,
		&sector->floor_bottom_right, &frame->left.r_pt)
		/ vec2_eucl_dist(sector->floor_bottom_left, sector->floor_top_left);
	frame->ground_uv.top_right.z = frame->outer_box.bottom_right.z;
}

static void	calc_inverse_of_z(t_xyz *left, t_xyz *right, t_xyz *current)
{
	*left = inv_z(*left);
	*right = inv_z(*right);
	*current = inv_z(*current);
}

void	calc_ground_texels(t_sector *sector, t_frame *frame, t_player *plr)
{
	plr = plr;
	calc_offsets(sector, frame);
	calc_inverse_of_z(&frame->ground_uv.top_left, &frame->ground_uv.top_right,
		&frame->ground_uv.bottom_left);
	frame->ground_uv_step.x = interpolate_points(frame->ground_uv.top_left.x,
		frame->ground_uv.top_right.x, frame->outer_box.bottom_left.x,
		frame->outer_box.bottom_right.x);
	frame->ground_uv_step.y = interpolate_points(frame->ground_uv.top_left.y,
		frame->ground_uv.bottom_left.y, frame->outer_box.bottom_left.y,
		SCREEN_HEIGHT);
	frame->ground_uv_step.z = interpolate_points(frame->ground_uv.top_left.z,
		frame->ground_uv.top_right.z, frame->outer_box.bottom_left.x,
		frame->outer_box.bottom_right.x);
}
