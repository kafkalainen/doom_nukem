/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ground_texels.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:54:25 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/21 14:11:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	calc_inverse_of_z(t_xyz *top_left, t_xyz *top_right,
	t_xyz *bottom_left, t_xyz *bottom_right)
{
	*top_left = inv_z(*top_left);
	*top_right = inv_z(*top_right);
	*bottom_left = inv_z(*bottom_left);
	*bottom_right = inv_z(*bottom_right);
}

void	calc_ground_texels(t_sector *sector, t_frame *frame)
{
	(void)sector;
	frame->ground_uv.top_left.x = frame->left.ground_uv_l.x;
	frame->ground_uv.top_left.y = frame->left.ground_uv_l.y;
	frame->ground_uv.top_left.z = frame->outer_box.bottom_left.z;
	frame->ground_uv.top_right.x = frame->left.ground_uv_r.x;
	frame->ground_uv.top_right.y = frame->left.ground_uv_r.y;
	frame->ground_uv.top_right.z = frame->outer_box.bottom_right.z;
	frame->ground_uv.bottom_left.x = frame->left.ground_uv_l.x;
	frame->ground_uv.bottom_left.y = frame->left.ground_uv_l.y;
	frame->ground_uv.bottom_left.z = 10.0f;
	frame->ground_uv.bottom_right.x = frame->left.ground_uv_r.x;
	frame->ground_uv.bottom_right.y = frame->left.ground_uv_r.y;
	frame->ground_uv.bottom_right.z = 10.0f;
	calc_inverse_of_z(
		&frame->ground_uv.top_left, &frame->ground_uv.top_right,
		&frame->ground_uv.bottom_left, &frame->ground_uv.bottom_right);
	frame->ground_uv_step.x = interpolate_points(
		frame->ground_uv.top_left.x, frame->ground_uv.top_right.x,
		frame->outer_box.bottom_left.x, frame->outer_box.bottom_right.x);
		// 0, 100);
	frame->ground_uv_step.y = interpolate_points(
		frame->ground_uv.top_left.y, frame->ground_uv.bottom_left.y,
		240, SCREEN_HEIGHT);
	frame->ground_uv_step.z = interpolate_points(
		frame->ground_uv.top_left.z, frame->ground_uv.bottom_left.z,
		240, SCREEN_HEIGHT);
}
