/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_dimensions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:27:42 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/05 15:30:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	calc_drawbox(t_plgn *box, int offset, t_point *x0, t_point *x1)
{
	// dist_traveled = fabsf(box->top_right.x - box->top_left.x)
	// 	/ fabsf(x1->x0.x - x0->x0.x);
	box->top_left.x = SCREEN_WIDTH - ((SCREEN_HEIGHT
				/ box->top_left.z) * box->top_left.x) + 15;
	box->top_right.x = SCREEN_WIDTH - ((SCREEN_HEIGHT
				/ box->top_right.z) * box->top_right.x) + 15;
	box->bottom_left = box->top_left;
	box->bottom_right = box->top_right;
	// if (x1->x0.x == box->top_right.x && x0->x0.x != box->top_left.x)
	// {
	// 	box->top_left.y = offset - SCREEN_HEIGHT / box->top_left.z * (x0->ceiling * dist_traveled);
	// 	box->top_right.y = offset - SCREEN_HEIGHT / box->top_right.z * x1->ceiling;
	// 	box->bottom_left.y = offset + SCREEN_HEIGHT / box->top_left.z
	// 		* (x0->ceiling - x0->ground) * dist_traveled;
	// 	box->bottom_right.y = offset + SCREEN_HEIGHT / box->top_right.z
	// 		* (x1->ceiling - x1->ground);
	// }
	// else if (x0->x0.x == box->top_left.x && x1->x0.x != box->top_right.x)
	// {
	// 	box->top_left.y = offset - SCREEN_HEIGHT / box->top_left.z * x0->ceiling * dist_traveled;
	// 	box->top_right.y = offset - SCREEN_HEIGHT / box->top_right.z * x1->ceiling;
	// 	box->bottom_left.y = offset + SCREEN_HEIGHT / box->top_left.z
	// 		* (x0->ceiling - x0->ground) * dist_traveled;
	// 	box->bottom_right.y = offset + SCREEN_HEIGHT / box->top_right.z
	// 		* (x1->ceiling - x1->ground);
	// } else {
	box->top_left.y = offset - SCREEN_HEIGHT / box->top_left.z * x0->ceiling;
	box->top_right.y = offset - SCREEN_HEIGHT / box->top_right.z * x1->ceiling;
	box->bottom_left.y = offset + SCREEN_HEIGHT / box->top_left.z
		* (x0->ceiling - x0->ground);
	box->bottom_right.y = offset + SCREEN_HEIGHT / box->top_right.z
		* (x1->ceiling - x1->ground);
}

static void	calc_z_x(t_plgn *box, t_xy *left_point, t_xy *right_point)
{
	box->top_left.z = vec2_perp_dist(*left_point);
	box->top_left.x = left_point->x;
	box->top_right.z = vec2_perp_dist(*right_point);
	box->top_right.x = right_point->x;
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
		frame->draw_top = frame->left.wall->ceiling - temp->next->ceiling;
		frame->draw_bottom = frame->left.wall->ground - temp->next->ground;
	}
	calc_z_x(&frame->outer_box, &frame->left.l_pt, &frame->left.r_pt);
	calc_z_x(&frame->inner_box, &frame->left.l_pt, &frame->left.r_pt);
	if (frame->draw_top || frame->draw_bottom)
		calc_drawbox(&frame->inner_box, plr->pitch + plr->height,
			temp, temp->next);
	calc_drawbox(&frame->outer_box, plr->pitch + plr->height,
		frame->left.wall, frame->left.wall->next);
	interpolate_steps(frame);
	frame->pitch = plr->pitch;
}
