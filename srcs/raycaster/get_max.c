/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:12:08 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/02 12:31:09 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

t_ray_fov			get_fov_points(t_point *plgn, t_home *home, t_player *plr, int i)
{
	t_point			*p0;
	t_point			*p1;
	t_ray_fov		ray;
	t_intersection	sect[2];
	while (home->sectors[i]->points)
	ray.ray_left.pos = plr->pos;
	ray.ray_right.pos = plr->pos;
	ray.ray_left.dir = vec2_rot(plr->dir, DEG_TO_RAD * -FOV * 0.5);
	ray.ray_right.dir = vec2_rot(plr->dir, DEG_TO_RAD * FOV * 0.5);
	calc_intersection(plgn, home->sectors[i]->points, &ray.ray_left, &sect[0]);
	calc_intersection(plgn, home->sectors[i]->points, &ray.ray_right, &sect[1]);
	ray.left_point = line_intersection(&sect[0]);
	ray.right_point = line_intersection(&sect[1]);
	return (ray);
}
