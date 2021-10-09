/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_distances_to_walls.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 11:37:18 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/09 08:30:35 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../headers/doom_nukem.h"

t_bool	check_if_too_close_to_a_wall(t_wall *wall, float width,
	t_xyz pos, t_xyz dir)
{
	t_xyz	isection;
	float	pow_width;

	isection = vec3(0.0f, 0.0f, 0.0f);
	pow_width = width * width;
	if (!check_if_open_portal(wall))
	{
		if (vec3_ray_triangle_intersect(&wall->top, pos, dir, &isection)
			&& get_distance_squared(isection, pos) < pow_width)
			return (true);
		if (vec3_ray_triangle_intersect(&wall->bot, pos, dir, &isection)
			&& get_distance_squared(isection, pos) < pow_width)
			return (true);
		if (vec2_get_distance_squared(wall->point, vec2(pos.x, pos.z))
			< pow_width && wall->bot.p[0].y < (pos.y + width)
			&& wall->top.p[1].y > (pos.y - width))
			return (true);
		if (vec2_get_distance_squared(wall->next->point, vec2(pos.x, pos.z))
			< pow_width && wall->bot.p[2].y < (pos.y + width)
			&& wall->top.p[2].y > (pos.y - width))
			return (true);
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

t_bool	check_if_too_close_to_a_door(t_wall *door, float width,
		t_xyz pos, t_xyz dir)
{
	t_xyz	left;
	t_xyz	right;
	t_xyz	behind;

	left = (t_xyz){-dir.z, dir.y, dir.x, 0.0f};
	right = (t_xyz){dir.z, dir.y, -dir.x, 0.0f};
	behind = vec3_mul(dir, -1.0f);
	if (check_if_too_close_to_a_wall(door, width, pos, dir))
		return (true);
	if (check_if_too_close_to_a_wall(door, width, pos, behind))
		return (true);
	if (check_if_too_close_to_a_wall(door, width, pos, left))
		return (true);
	if (check_if_too_close_to_a_wall(door, width, pos, right))
		return (true);
	return (false);
}
