/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:31:48 by rzukale           #+#    #+#             */
/*   Updated: 2021/08/24 13:47:03 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float	get_distance_squared(t_xyz pt0, t_xyz pt1)
{
	return (((pt1.x - pt0.x) * (pt1.x - pt0.x) +
		(pt1.y - pt0.y) * (pt1.y - pt0.y) +
		(pt1.z - pt0.z) * (pt1.z - pt0.z)));
}

void	choose_new_direction(t_entity *entity, t_home *home)
{
	int		dir;
	t_xyz	pos;

	(void)home;
	dir = rand() % 8;
	dir = 0;
	if (dir == 0) // move south
	{
		pos.x = S;
		pos.y = 0;
		pos.z = 0;
		pos.w = 1;
		entity->dir = vec3_unit_vector(vec3_dec(entity->pos, pos));
		// entity->top = rotate_triangle(&entity->top, 180, 'y');
		// entity->bot = rotate_triangle(&entity->bot, 180, 'y');
		// entity->dir = triangle_normal(&entity->top);
	}
	if (dir == 1) // move south-west
		entity->dir.x = SW;
	if (dir == 2) // move west
		entity->dir.x = W;
	if (dir == 3) // move north-west
		entity->dir.x = NW;
	if (dir == 4) // move north
		entity->dir.x = N;
	if (dir == 5) // move north-east
		entity->dir.x = NE;
	if (dir == 6) // move east
		entity->dir.x = E;
	if (dir == 7) // move south-east
		entity->dir.x = SE;
}
