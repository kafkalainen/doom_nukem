/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_distances_to_walls.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 11:37:18 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/28 12:50:20 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../headers/doom_nukem.h"

static t_bool	check_if_too_close_to_a_wall(t_wall *wall, float width,
	t_xyz pos, t_xyz dir)
{
	t_xyz	isection;

	if (wall->top.type < 0)
	{
		if (vec3_ray_triangle_intersect(&wall->top, pos, dir, &isection))
		{
			if (get_distance_squared(isection, pos) < width * width)
				return (true);
		}
		if (vec3_ray_triangle_intersect(&wall->bot, pos, dir, &isection))
		{
			if (get_distance_squared(isection, pos) < width * width)
				return (true);
		}
	}
	return (false);
}

t_wall	*check_if_too_close_to_walls(t_sector *sector, float width,
		t_xyz pos, t_xyz dir)
{
	t_wall	*wall;
	t_xyz	left;
	t_xyz	right;
	t_xyz	behind;
	Uint32	i;

	i = 0;
	left = (t_xyz){-dir.z, dir.y, dir.x, 0.0f};
	right = (t_xyz){dir.z, dir.y, -dir.x, 0.0f};
	behind = vec3_mul(dir, -1.0f);
	wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (check_if_too_close_to_a_wall(wall, width, pos, dir))
			return (wall);
		if (check_if_too_close_to_a_wall(wall, width, pos, behind))
			return (wall);
		if (check_if_too_close_to_a_wall(wall, width, pos, left))
			return (wall);
		if (check_if_too_close_to_a_wall(wall, width, pos, right))
			return (wall);
		wall = wall->next;
		i++;
	}
	return (NULL);
}
