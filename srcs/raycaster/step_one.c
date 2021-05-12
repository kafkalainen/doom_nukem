/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:45:45 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/12 14:45:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	step_one(t_frame *frame)
{
	frame->inner_box.top_left.y -= frame->step_inner_top.y;
	frame->inner_box.top_left.z -= frame->step_inner_top.z;
	frame->inner_box.bottom_left.y -= frame->step_inner_bot.y;
	frame->outer_box.top_left.y -= frame->step_outer_top.y;
	frame->outer_box.top_left.z -= frame->step_outer_top.z;
	frame->outer_box.bottom_left.y -= frame->step_outer_bot.y;
	frame->middle_uv.top_left.x += frame->uv_step.x;
	frame->middle_uv.top_left.z += frame->uv_step.z;
	frame->ground_uv.top_left.x += frame->ground_uv_step.x;
	frame->ground_uv.top_left.z += frame->uv_step.z;
	frame->outer_box.top_left.x += 1;
	frame->outer_box.bottom_left.x += 1;
	frame->inner_box.top_left.x += 1;
	frame->inner_box.bottom_left.x += 1;
}
