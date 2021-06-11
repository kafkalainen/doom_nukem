/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_l_pt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:33:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/22 14:07:34 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"


/*
**	ERRORZ
*/
// static int	check_if_same_wall(t_xy a, t_xy b, t_xy r_point)
// {
// 	if (a.x == b.x && a.y == b.y)
// 	{
// 		if (r_point.x != -1 && r_point.y != -1)
// 			return (1);
// 		else
// 			return (0);
// 	}
// 	else
// 		return (0);
// }

void	get_r_pt(t_wall *start, t_ray ray, t_frame *frame, int walls)
{
	t_intersection	sect;
	t_wall			*wall;

	wall = start;
	while (walls)
	{
		calc_intersection(wall, &ray, &sect);
		frame->right.r_pt = line_intersection(&sect);
		if (frame->right.r_pt.x != -1)
			break ;
		wall = wall->next;
		walls--;
	}
	frame->right.wall = wall;
}

void	get_l_pt(t_wall *start, t_ray ray, t_frame *frame, int walls)
{
	t_intersection	sect;
	t_wall			*wall;

	wall = start;
	while (walls)
	{
		calc_intersection(wall, &ray, &sect);
		frame->left.l_pt = line_intersection(&sect);
		if (frame->left.l_pt.x != -1)
			break ;
		wall = wall->next;
		walls--;
	}
	frame->left.wall = wall;
}

void	get_wall_pts(t_frame *frame, int walls, t_player *plr)
{
	t_ray	ray;

	ray.pos = (t_xy){plr->pos.x, plr->pos.z};
	ray.dir = frame->left.left_dir;
	get_l_pt(frame->left.wall, ray, frame, walls);
	ray.dir = frame->right.right_dir;
	get_r_pt(frame->left.wall, ray, frame, walls);
	// if (check_if_same_wall(frame->left.wall->x0,
	// 		frame->right.wall->x0, frame->right.r_pt))
	// {
	// 	frame->left.r_pt = frame->right.r_pt;
	// 	frame->left.height_r = frame->right.height_r;
	// 	frame->left.ground_uv_r = frame->right.ground_uv_r;
	// }
}
