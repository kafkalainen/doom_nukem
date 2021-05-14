/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_dimensions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:27:42 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/14 22:46:47 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	calc_drawbox(t_plgn *box, int offset, t_height *x0,
	t_height *x1, t_player *plr)
{
	t_height	height_left;
	t_height	height_right;

	height_left.ceiling = (x0->ceiling - plr->z);
	height_left.ground = (x0->ground - plr->z);
	height_right.ceiling = (x1->ceiling - plr->z);
	height_right.ground = (x1->ground - plr->z);
	box->top_left.x = SCREEN_WIDTH / 2 - ((SCREEN_HEIGHT
				/ box->top_left.z) * box->top_left.x);
	box->top_right.x = SCREEN_WIDTH / 2 - ((SCREEN_HEIGHT
				/ box->top_right.z) * box->top_right.x);
	box->bottom_left = box->top_left;
	box->bottom_right = box->top_right;
	box->top_left.y = offset - SCREEN_HEIGHT / box->top_left.z
		* height_left.ceiling;
	box->top_right.y = offset - SCREEN_HEIGHT / box->top_right.z
		* height_right.ceiling;
	box->bottom_left.y = offset + SCREEN_HEIGHT / box->top_left.z
		* (10 - height_left.ground);
	box->bottom_right.y = offset + SCREEN_HEIGHT / box->top_right.z
		* (10 - height_right.ground);
}

static void	calc_z_x(t_plgn *box, t_xy *left_point, t_xy *right_point)
{
	box->top_left.z = left_point->y;
	box->top_left.x = left_point->x;
	box->top_right.z = right_point->y;
	box->top_right.x = right_point->x;
}

static void	interpolate_steps(t_frame *frame)
{
	frame->step_outer_top.y = interpolate_points(
			frame->outer_box.top_right.y, frame->outer_box.top_left.y,
			frame->outer_box.top_left.x, frame->outer_box.top_right.x);
	frame->step_outer_top.z = interpolate_points(
			frame->outer_box.top_left.y, frame->outer_box.top_right.y,
			frame->outer_box.top_left.x, frame->outer_box.top_right.x);
	frame->step_outer_bot.y = interpolate_points(
			frame->outer_box.bottom_right.y, frame->outer_box.bottom_left.y,
			frame->outer_box.top_left.x, frame->outer_box.top_right.x);
	frame->step_inner_top.y = interpolate_points(
			frame->inner_box.top_right.y, frame->inner_box.top_left.y,
			frame->inner_box.top_left.x, frame->inner_box.top_right.x);
	frame->step_inner_top.z = interpolate_points(
			frame->inner_box.top_left.y, frame->inner_box.top_right.y,
			frame->inner_box.top_left.x, frame->inner_box.top_right.x);
	frame->step_inner_bot.y = interpolate_points(
			frame->inner_box.bottom_right.y, frame->inner_box.bottom_left.y,
			frame->inner_box.top_left.x, frame->inner_box.top_right.x);
}

void	calc_dimensions(t_frame *frame, t_player *plr, t_home *home)
{
	t_point	*temp;

	frame->draw_top = 0;
	frame->draw_bottom = 0;
	frame->draw_middle = 0;
	frame->draw_incline = 0;
	if (frame->left.wall->idx < 0)
		frame->draw_middle = 1;
	if (frame->left.wall->idx >= 0)
	{
		temp = get_portal_by_idx(frame->idx,
				home->sectors[frame->left.wall->idx]);
		frame->draw_top = frame->left.wall->height.ceiling
			- temp->next->height.ceiling;
		frame->draw_bottom = frame->left.wall->height.ground
			- temp->next->height.ground;
	}
	calc_z_x(&frame->outer_box, &frame->left.l_pt, &frame->left.r_pt);
	calc_z_x(&frame->inner_box, &frame->left.l_pt, &frame->left.r_pt);
	frame->ground_uv.bottom_left.z = plr->height * 10 + plr->pitch;
	if (frame->draw_top || frame->draw_bottom)
		calc_drawbox(&frame->inner_box, plr->pitch + plr->height * 10,
			&temp->height, &temp->next->height, plr);
	calc_drawbox(&frame->outer_box, plr->pitch + plr->height * 10,
		&frame->left.height_l, &frame->left.height_r, plr);
	interpolate_steps(frame);
	frame->pitch = plr->pitch;
}
