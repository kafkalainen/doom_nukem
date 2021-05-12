/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ground_texels.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:54:25 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/12 15:24:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static float	vec2_dist_from_point(t_xy *x1, t_xy *x2, t_xy *x0)
{
	return (fabsf(((x2->x - x1->x) * (x1->y - x0->y)
		- (x1->x - x0->x) * (x2->y - x1->y)))
		/ vec2_eucl_dist(*x1, *x2));
}

static float	clip_to_0_1_range(float nb)
{
	if (nb < 0.0f)
		return (0.0f);
	else if (nb > 1.0f)
		return (1.0f);
	else
		return (nb);
}

static void	clip_offsets_to_range(t_plgn *ground_uv)
{
	ground_uv->top_left.x = clip_to_0_1_range(ground_uv->top_left.x);
	ground_uv->top_left.y = clip_to_0_1_range(ground_uv->top_left.y);
	ground_uv->top_right.x = clip_to_0_1_range(ground_uv->top_right.x);
	ground_uv->top_right.y = clip_to_0_1_range(ground_uv->top_right.y);
	ground_uv->bottom_left.x = clip_to_0_1_range(ground_uv->bottom_left.x);
	ground_uv->bottom_left.y = clip_to_0_1_range(ground_uv->bottom_left.y);
	ground_uv->bottom_right.x = clip_to_0_1_range(ground_uv->bottom_right.x);
	ground_uv->bottom_right.y = clip_to_0_1_range(ground_uv->bottom_right.y);
}

static void	calc_offsets(t_sector *sector, t_frame *frame)
{
	frame->ground_uv.top_left.x = vec2_dist_from_point(&sector->floor_top_right,
		&sector->floor_bottom_right, &frame->left.l_pt)
		/ vec2_eucl_dist(sector->floor_top_right, sector->floor_top_left);
	frame->ground_uv.top_left.y = vec2_dist_from_point(&sector->floor_bottom_left,
		&sector->floor_bottom_right, &frame->left.l_pt)
		/ vec2_eucl_dist(sector->floor_bottom_left, sector->floor_top_left);
	frame->ground_uv.top_left.z = frame->outer_box.top_left.z;
	frame->ground_uv.top_right.x = vec2_dist_from_point(&sector->floor_top_right,
		&sector->floor_bottom_right, &frame->left.r_pt)
		/ vec2_eucl_dist(sector->floor_top_right, sector->floor_top_left);
	frame->ground_uv.top_right.y = vec2_dist_from_point(&sector->floor_bottom_left,
		&sector->floor_bottom_right, &frame->left.r_pt)
		/ vec2_eucl_dist(sector->floor_bottom_left, sector->floor_top_left);
	frame->ground_uv.top_right.z = frame->outer_box.top_right.z;
	frame->ground_uv.bottom_left.x = frame->ground_uv.top_left.x;
	frame->ground_uv.bottom_left.y = vec2_dist_from_point(&sector->floor_bottom_left,
		&sector->floor_bottom_right, &(t_xy){0.0f, 0.0f})
		/ vec2_eucl_dist(sector->floor_bottom_left, sector->floor_top_left);
	frame->ground_uv.bottom_left.z = 0.0f;
	frame->ground_uv.bottom_right.x = frame->ground_uv.top_right.x;
	frame->ground_uv.bottom_right.y = vec2_dist_from_point(&sector->floor_bottom_left,
		&sector->floor_bottom_right, &(t_xy){0.0f, 0.0f})
		/ vec2_eucl_dist(sector->floor_bottom_left, sector->floor_top_left);
	frame->ground_uv.bottom_right.z = 0.0f;
}

static void	calc_inverse_of_z(t_xyz *top_left, t_xyz *top_right,
	t_xyz *bottom_left, t_xyz *bottom_right)
{
	*top_left = inv_z(*top_left);
	*top_right = inv_z(*top_right);
	*bottom_left = inv_z(*bottom_left);
	*bottom_right = inv_z(*bottom_right);
}

void	calc_ground_texels(t_sector *sector, t_frame *frame, t_player *plr)
{
	plr = plr;
	calc_offsets(sector, frame);
	clip_offsets_to_range(&frame->ground_uv);
	calc_inverse_of_z(&frame->ground_uv.top_left, &frame->ground_uv.top_right,
		&frame->ground_uv.bottom_left, &frame->ground_uv.bottom_right);
	frame->ground_uv_step.x = interpolate_points(frame->ground_uv.top_left.x,
		frame->ground_uv.top_right.x, frame->outer_box.bottom_left.x,
		frame->outer_box.bottom_right.x);
	frame->ground_uv_step.y = interpolate_points(frame->ground_uv.bottom_left.y,
		frame->ground_uv.top_left.y, SCREEN_HEIGHT,
		frame->outer_box.bottom_left.y);
	frame->ground_uv_step.z = interpolate_points(frame->ground_uv.bottom_left.z,
		frame->ground_uv.top_left.z, SCREEN_HEIGHT,
		frame->outer_box.bottom_left.y);
}
