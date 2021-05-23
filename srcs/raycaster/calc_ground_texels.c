/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ground_texels.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:54:25 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/21 17:07:54 by jnivala          ###   ########.fr       */
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

void	calc_ground_texels(t_frame *frame)
{
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
	frame->ground_uv_step_delta_u.x = (frame->ground_uv.top_right.x - frame->ground_uv.top_left.x) / 320;
	frame->ground_uv_step_delta_u.y = (frame->ground_uv.top_right.y - frame->ground_uv.top_left.y) / 320;
	frame->ground_uv_step_delta_u.z = (frame->ground_uv.top_right.z - frame->ground_uv.top_left.z) / 320;
	frame->ground_uv_step_delta_v.x = (frame->ground_uv.bottom_right.x - frame->ground_uv.top_left.x) / 240;
	frame->ground_uv_step_delta_v.y = (frame->ground_uv.bottom_right.y - frame->ground_uv.top_left.y) / 240;
	frame->ground_uv_step_delta_v.z = (frame->ground_uv.bottom_right.z - frame->ground_uv.top_left.z) / 240;
}
