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

#include "../../doom_nukem.h"

void		get_r_pt(t_point *start, t_ray_pt *fov, t_frame *frame, int walls)
{
	t_ray			ray;
	t_intersection	sect;
	t_point			*p0;

	ray.pos = vec2(0, 0);
	ray.dir = vec2_rot(vec2(0, 1), -frame->max_fov * frame->min_step);
	p0 = start;
	while (walls)
	{
		if (p0->x0.y >= 0 || p0->next->x0.y >= 0)
		{
			calc_intersection(p0, &ray, &sect);
			fov->r_pt = line_intersection(&sect);
			if (fov->r_pt.y != -1)
				break ;
		}
		p0 = p0->next;
		walls--;
	}
	fov->wall = p0;
	fov->l_pt = fov->wall->x0;
}

void	get_l_pt(t_point *start, t_ray_pt *fov, t_frame *frame, int walls)
{
	t_ray			ray;
	t_intersection	sect;
	t_point			*p0;

	ray.pos = vec2(0, 0);
	ray.dir = vec2_rot(vec2(0, 1), -frame->offset * frame->min_step);
	p0 = start;
	while (walls)
	{
		if (p0->x0.y >= 0 || p0->next->x0.y >= 0)
		{
			calc_intersection(p0, &ray, &sect);
			fov->l_pt = line_intersection(&sect);
			if (fov->l_pt.y != -1)
				break ;
		}
		p0 = p0->next;
		walls--;
	}
	fov->wall = p0;
	fov->r_pt = fov->wall->next->x0;
<<<<<<< HEAD
}

void	get_wall_pts(t_frame *frame, int walls, int current_pxl)
{
	if(current_pxl == 0)
	{
		get_l_pt(frame->left.wall, &frame->left, frame, walls);
		get_r_pt(frame->left.wall, &frame->right, frame, walls);
	}
	else
	{
		frame->left.wall = frame->left.wall->next;
		frame->left.l_pt = frame->left.wall->x0;
		frame->left.r_pt = frame->left.wall->next->x0;
	}
	if (check_if_same_wall(frame->left.wall->x0, 
=======
	get_r_pt(frame->left.wall, &frame->right, frame, walls);
	if (check_if_same_wall(frame->left.wall->x0,
>>>>>>> cfb26cb6ba6f2a9a865c527c7e1dcd648ec93874
		frame->right.wall->x0, frame->right.r_pt))
		frame->left.r_pt = frame->right.r_pt;
}
