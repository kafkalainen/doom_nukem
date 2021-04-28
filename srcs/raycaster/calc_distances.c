/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distances.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:27:42 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/28 15:45:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	calc_distances(t_frame *frame, t_player *plr, int *ground,
	int *ceiling)
{
	frame->box.top_left.z  = vec2_perp_dist(frame->left.l_pt);
	frame->box.top_right.z = vec2_perp_dist(frame->left.r_pt);
	frame->box.top_left.x = SCREEN_WIDTH - ((SCREEN_HEIGHT
				/ frame->box.top_left.z) * frame->left.l_pt.x) + 15;
	frame->box.top_right.x = SCREEN_WIDTH - ((SCREEN_HEIGHT
				/ frame->box.top_right.z) * frame->left.r_pt.x) + 15;
	frame->box.bottom_left = frame->box.top_left;
	frame->box.bottom_right = frame->box.top_right;
	frame->box.top_left.y = plr->pitch - SCREEN_HEIGHT /
		frame->box.top_left.z * *ceiling;
	frame->box.top_right.y = plr->pitch - SCREEN_HEIGHT /
		frame->box.top_right.z * *ceiling;
	frame->box.bottom_left.y = plr->pitch + SCREEN_HEIGHT /
		frame->box.top_left.z * (*ceiling - *ground);
	frame->box.bottom_right.y = plr->pitch + SCREEN_HEIGHT /
		frame->box.top_right.z * (*ceiling - *ground);
	frame->step_top.y = interpolate_points(frame->box.top_right.y, frame->box.top_left.y,
			frame->box.top_left.x, frame->box.top_right.x);
	frame->step_top.z = interpolate_points(frame->box.top_left.y, frame->box.top_right.y,
			frame->box.top_left.x, frame->box.top_right.x);
	frame->step_bot.y = interpolate_points(frame->box.bottom_right.y, frame->box.bottom_left.y,
			frame->box.top_left.x, frame->box.top_right.x);
	frame->pitch = plr->pitch;
}
