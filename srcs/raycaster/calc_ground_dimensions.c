/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ground_dimensions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 15:37:18 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/21 14:12:24 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	calc_ground_drawbox(t_frame *frame, t_player *plr,
	t_height *left_bottom, t_height *right_bottom)
{
	t_height	height_top_left;
	t_height	height_top_right;
	t_height	height_bottom_left;
	t_height	height_bottom_right;

	height_top_left.ground = (frame->left.height_l.ground - plr->z);
	height_top_right.ground = (frame->left.height_r.ground - plr->z);
	height_bottom_left.ground = (left_bottom->ground - plr->z);
	height_bottom_right.ground = (right_bottom->ground - plr->z);
	frame->inner_box.top_left.x = SCREEN_WIDTH / 2 - ((SCREEN_HEIGHT
				/ frame->inner_box.top_left.z) * frame->inner_box.top_left.x);
	frame->inner_box.top_right.x = SCREEN_WIDTH / 2 - ((SCREEN_HEIGHT
				/ frame->inner_box.top_left.z) * frame->inner_box.top_right.x);
	frame->inner_box.bottom_left.x = SCREEN_WIDTH / 2 - ((SCREEN_HEIGHT
				/ frame->inner_box.bottom_left.z) * frame->inner_box.bottom_left.x);
	frame->inner_box.bottom_right.x = SCREEN_WIDTH / 2 - ((SCREEN_HEIGHT
				/ frame->inner_box.bottom_right.z) * frame->inner_box.bottom_right.x);
	frame->inner_box.top_left.y = (plr->pitch + plr->height * 10) + SCREEN_HEIGHT
		/ frame->inner_box.top_left.z * (10 - height_top_left.ground);
	frame->inner_box.top_right.y = (plr->pitch + plr->height * 10) + SCREEN_HEIGHT
		/ frame->inner_box.top_right.z * (10 - height_top_right.ground);
	frame->inner_box.bottom_left.y = (plr->pitch + plr->height * 10) + SCREEN_HEIGHT
		/ frame->inner_box.bottom_left.z * (10 - height_bottom_left.ground);
	frame->inner_box.bottom_right.y = (plr->pitch + plr->height * 10) + SCREEN_HEIGHT
		/ frame->inner_box.bottom_right.z * (10 - height_bottom_right.ground);
}

// static t_height	interpolate_height(t_xy *cutpoint, t_xy *dir, t_point *start, int walls)
// {
// 	t_height		height;

// 	*cutpoint = cast_ray(dir, &start, walls);
// 	interpolate_y(&height, *cutpoint, start, start->next);
// 	return (height);
// }

static void	assign_z_x(t_plgn *box, t_frame *frame,
	t_xy *bottom_left, t_xy *bottom_right)
{
	(void)bottom_left;
	(void)bottom_right;
	box->top_left.z = frame->left.l_pt.y;
	box->top_left.x = frame->left.l_pt.x;
	box->top_right.z = frame->right.r_pt.y;
	box->top_right.x = frame->right.r_pt.x;
	box->bottom_left.z = 0.1f;
	box->bottom_left.x =  frame->left.l_pt.x;
	box->bottom_right.z = 0.1f;
	box->bottom_right.x =  frame->right.r_pt.y;
}

static void init_drawboxes(t_frame *frame)
{
	frame->draw_ground = 1;
}

static void	interpolate_ground_steps(t_frame *frame)
{
	frame->step_ground_left_top.x = interpolate_points(
			frame->inner_box.top_left.x, frame->inner_box.bottom_left.x,
			frame->inner_box.top_left.y, frame->inner_box.bottom_left.y);
	frame->step_ground_right_top.x = interpolate_points(
			frame->inner_box.top_right.x, frame->inner_box.bottom_right.x,
			frame->inner_box.top_right.y, frame->inner_box.bottom_right.y);
	frame->step_inner_top.z = interpolate_points(
			frame->inner_box.top_left.y, frame->inner_box.top_right.y,
			frame->inner_box.top_left.y, frame->inner_box.bottom_left.y);
}

void			calc_ground_dimensions(t_frame *frame, t_player *plr, t_home *home)
{
	t_xy			cutpoints[2];
	t_height		left_ground;
	t_height		right_ground;
	unsigned int	walls;

	walls = home->sectors[frame->idx]->nb_of_walls;
	init_drawboxes(frame);
	get_l_pt(frame->left.wall, &frame->left, frame, walls);
	get_r_pt(frame->left.wall, &frame->right, frame, walls);
	assign_z_x(&frame->inner_box, frame, &cutpoints[0], &cutpoints[1]);
	calc_ground_drawbox(frame, plr, &left_ground, &right_ground);
	interpolate_ground_steps(frame);
}
