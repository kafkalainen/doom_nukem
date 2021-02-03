/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fov.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:12:08 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/03 13:59:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"


/*
** 1. Screen space is divided to ratios of the angles of the fov.
** 2. Leftmost angle is left_point to next wallpoint of the left_point
** 3. Left_po
** 4.
** 6.
*/
void				calc_angles(t_ray_fov *fov, t_sector *sector)
{
	t_point		*current;
	t_point		*next;
	float		angle;

	if (fov->left_wall == fov->right_wall)
	{
		fov->left_wall->wall_rad = FOV * DEG_TO_RAD;
		return ;
	}
	current = loop_list(sector->points, fov->left_wall->next);
	fov->left_wall->wall_rad = vec2_angle(fov->left_point, current->x0);
	angle += fov->left_wall->wall_rad;
	while (angle < FOV * DEG_TO_RAD)
	{
		next = loop_list(sector->points, current->next);
		current->wall_rad = vec2_angle(current->x0, next->x0);
		angle += current->wall_rad;
		current = loop_list(sector->points, current->next);
	}
	if (current == fov->right_wall)
		current->wall_rad = FOV * DEG_TO_RAD - (angle - current->wall_rad);
}

t_ray_fov			get_fov(t_home *home, t_player *plr, int i)
{
	t_point			*p0;
	t_ray_fov		ray;
	t_intersection	sect;

	ray.ray_right.pos = vec2(0, 0);
	ray.ray_left.pos = vec2(0, 0);
	ray.left_point = vec2(-1, -1);
	ray.right_point = vec2(-1, -1);
	p0 = home->sectors[i]->points;
	while (ray.left_point.y == -1.0f)
	// while (p0 && ray.left_point.y == -1.0f)
	{
		ray.ray_left.dir = vec2_rot(plr->dir, DEG_TO_RAD * -FOV * 0.5f);
		calc_intersection(p0, home->sectors[i]->points, &ray.ray_left, &sect);
		ray.left_point = line_intersection(&sect);
		if (ray.left_point.y == -1.0f)
			// p0 = p0->next;
			p0 = loop_list(home->sectors[i]->points, p0->next);
	}
	ray.left_wall = p0;
	p0 = home->sectors[i]->points;
	while (ray.right_point.y == -1.0f)
	// while (p0 && ray.right_point.y == -1.0f)
	{
		ray.ray_right.dir = vec2_rot(plr->dir, DEG_TO_RAD * FOV * 0.5f);
		calc_intersection(p0, home->sectors[i]->points, &ray.ray_right, &sect);
		ray.right_point = line_intersection(&sect);
		if (ray.right_point.y == -1.0f)
			// p0 = p0->next;
			p0 = loop_list(home->sectors[i]->points, p0->next);
	}
	ray.right_wall = p0;
	return (ray);
}
