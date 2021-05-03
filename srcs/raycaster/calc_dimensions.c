/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_dimensions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:27:42 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/03 14:25:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	calc_drawbox(t_plgn *box, t_player *plr, int ground,
	int ceiling)
{
	box->top_left.x = SCREEN_WIDTH - ((SCREEN_HEIGHT
				/ box->top_left.z) * box->top_left.x) + 15;
	box->top_right.x = SCREEN_WIDTH - ((SCREEN_HEIGHT
				/ box->top_right.z) * box->top_right.x) + 15;
	box->bottom_left = box->top_left;
	box->bottom_right = box->top_right;
	box->top_left.y = (plr->pitch + plr->height) - SCREEN_HEIGHT
		/ box->top_left.z * ceiling;
	box->top_right.y = (plr->pitch + plr->height) - SCREEN_HEIGHT
		/ box->top_right.z * ceiling;
	box->bottom_left.y = (plr->pitch + plr->height) + SCREEN_HEIGHT
		/ box->top_left.z * (ceiling - ground);
	box->bottom_right.y = (plr->pitch + plr->height) + SCREEN_HEIGHT
		/ box->top_right.z * (ceiling - ground);
}

static void	calc_z_x(t_plgn *plgn, t_xy *left_point, t_xy *right_point)
{
	plgn->top_left.z = vec2_perp_dist(*left_point);
	plgn->top_left.x = left_point->x;
	plgn->top_right.z = vec2_perp_dist(*right_point);
	plgn->top_right.x = right_point->x;
}

static void	interpolate_steps(t_frame *frame)
{
	frame->step_outer_top.y = interpolate_points(frame->outer_box.top_right.y,
			frame->outer_box.top_left.y, frame->outer_box.top_left.x,
			frame->outer_box.top_right.x);
	frame->step_outer_top.z = interpolate_points(frame->outer_box.top_left.y,
			frame->outer_box.top_right.y, frame->outer_box.top_left.x,
			frame->outer_box.top_right.x);
	frame->step_outer_bot.y = interpolate_points(
			frame->outer_box.bottom_right.y,
			frame->outer_box.bottom_left.y, frame->outer_box.top_left.x,
			frame->outer_box.top_right.x);
	frame->step_inner_top.y = interpolate_points(
			frame->inner_box.top_right.y,
			frame->inner_box.top_left.y, frame->inner_box.top_left.x,
			frame->inner_box.top_right.x);
	frame->step_inner_top.z = interpolate_points(
			frame->inner_box.top_left.y,
			frame->inner_box.top_right.y, frame->inner_box.top_left.x,
			frame->inner_box.top_right.x);
	frame->step_inner_bot.y = interpolate_points(
			frame->inner_box.bottom_right.y,
			frame->inner_box.bottom_left.y, frame->inner_box.top_left.x,
			frame->inner_box.top_right.x);
}

void	calc_dimensions(t_frame *frame, t_player *plr, t_home *home)
{
	frame->draw_top = 0;
	frame->draw_bottom = 0;
	frame->draw_middle = 0;
	if (frame->left.wall->idx < 0)
		frame->draw_middle = 1;
	if (frame->left.wall->idx >= 0)
		frame->draw_top = home->sectors[frame->idx]->ceiling
			- home->sectors[frame->left.wall->idx]->ceiling;
	if (frame->left.wall->idx >= 0)
		frame->draw_bottom = home->sectors[frame->idx]->ground
			- home->sectors[frame->left.wall->idx]->ground;
	calc_z_x(&frame->outer_box, &frame->left.l_pt, &frame->left.r_pt);
	calc_z_x(&frame->inner_box, &frame->left.l_pt, &frame->left.r_pt);
	if (frame->draw_top || frame->draw_bottom)
		calc_drawbox(&frame->inner_box, plr,
			home->sectors[frame->left.wall->idx]->ground,
			home->sectors[frame->left.wall->idx]->ceiling);
	calc_drawbox(&frame->outer_box, plr,
		home->sectors[frame->idx]->ground, home->sectors[frame->idx]->ceiling);
	interpolate_steps(frame);
	frame->pitch = plr->pitch;
}
