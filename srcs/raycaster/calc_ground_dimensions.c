/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ground_dimensions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 15:37:18 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/18 14:26:40 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// static void	calc_ground_drawbox(t_plgn *box, int offset, t_height *x0,
// 	t_height *x1, t_player *plr)
// {
// 	t_height	height_top_left;
// 	t_height	height_top_right;
// 	t_height	height_bottom_left;
// 	t_height	height_bottom_right;

// 	height_top_left.ground = (x0->ground - plr->z);
// 	height_top_right.ground = (x0->ground - plr->z);
// 	height_bottom_left.ground = (x1->ground - plr->z);
// 	height_bottom_right.ground = (x1->ground - plr->z);
// 	box->top_left.x = SCREEN_WIDTH / 2 - ((SCREEN_HEIGHT
// 				/ box->top_left.z) * box->top_left.x);
// 	box->top_right.x = SCREEN_WIDTH / 2 - ((SCREEN_HEIGHT
// 				/ box->top_right.z) * box->top_right.x);
// 	box->bottom_left.x = SCREEN_WIDTH / 2 - ((SCREEN_HEIGHT
// 				/ box->bottom_left.z) * box->bottom_left.x);
// 	box->bottom_right.x = SCREEN_WIDTH / 2 - ((SCREEN_HEIGHT
// 				/ box->bottom_right.z) * box->bottom_right.x);
// 	box->top_left.y = offset - SCREEN_HEIGHT / box->top_left.z
// 		* (10 - height_top_left.ground);
// 	box->top_right.y = offset - SCREEN_HEIGHT / box->top_right.z
// 		* (10 - height_top_right.ground);
// 	box->bottom_left.y = offset + SCREEN_HEIGHT / box->top_left.z
// 		* (10 - height_bottom_left.ground);
// 	box->bottom_right.y = offset + SCREEN_HEIGHT / box->top_right.z
// 		* (10 - height_bottom_right.ground);
// }

// static t_point	*check_for_height_difference(t_frame *frame, unsigned int walls)
// {
// 	t_point			*wall;
// 	unsigned int	i;

// 	i = 0;
// 	wall = frame->left.wall;
// 	while (i < walls)
// 	{
// 		if (wall->height.ground != wall->next->height.ground)
// 			return (wall);
// 		i++;
// 	}
// 	return (NULL);
// }

/*
**	1. Find highest point.
**	2. Assign opposing walls.
**	3. Slant all the walls based on highest point and opposing wall.
**	2. If there is a height difference, a line should be drawn between the opposing wall.
*/
// void			calc_ground_dimensions(t_frame *frame, t_player *plr, t_home *home)
// {
// 	t_point	*temp_x0;

// 	(void)plr;
// 	get_l_pt(frame->left.wall, &frame->left, frame,
// 		home->sectors[frame->idx]->nb_of_walls);
// 	get_r_pt(frame->left.wall, &frame->right, frame,
// 		home->sectors[frame->idx]->nb_of_walls);
// 	temp_x0 = frame->left.wall;
// 	while (temp_x0 != frame->right.wall)
// 	{
// 		temp_x0 = temp_x0->next;
// 	}
// 	frame->right.l_pt;
	// frame->right.r_pt;
	// ground_diff = check_for_height_difference(frame, home->sectors[frame->idx]->nb_of_walls);
	// if (ground_diff)
	// {

	// }
	// else
	// {

	// }
// }
