/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:31:48 by rzukale           #+#    #+#             */
/*   Updated: 2021/06/28 15:00:18 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	check_aggro(t_player *plr, t_entity *entity, t_sector *sector)
{
	float			distance_squared;
	Uint32			signed_dst;
	unsigned int	i;
	t_wall			*wall;

	distance_squared = ((plr->pos.x - entity->pos.x) * (plr->pos.x - entity->pos.x) +
		(plr->pos.y - entity->pos.y) * (plr->pos.y - entity->pos.y) +
		(plr->pos.z - entity->pos.z) * (plr->pos.z - entity->pos.z));
	signed_dst = vec3_signed_distance_to_plane(plr->pos, entity->dir, entity->pos);
	if (distance_squared <= AGGRO_RANGE_1 && signed_dst == 0 && plr->cur_sector == entity->sector_idx)
	{
		entity->is_aggroed = 1;
		return (1);
	}
	if (distance_squared <= AGGRO_RANGE_1 && signed_dst == 0 && plr->cur_sector != entity->sector_idx)
	{
		wall = sector->walls;
		i = 0;
		while (i < sector->nb_of_walls)
		{
			if (check_if_portal(wall))
			{
				if ((wall->is_door && !wall->is_closed) || !wall->is_door)
				{
					if (check_intersection(wall, vec3_to_vec2(entity->pos), vec3_to_vec2(plr->pos)))
					{
						entity->is_aggroed = 1;
						return (1);
					}
				}
			}
			i++;
			wall = wall->next;
		}
	}
	if (distance_squared <= 1)
	{
		entity->is_aggroed = 1;
		return (1);
	}
	return (0);
}

int	entity_move(t_entity *entity, t_home *home, Uint32 t)
{
	t_wall			*wall;
	t_xyz			new_loc;

	// plr->move_dir.y = 0.0f;
	// plr->move_dir = vec3_unit_vector(plr->move_dir);
	new_loc = vec3_add(entity->pos, vec3_mul(entity->dir, t * 0.005f));
	// if (check_distance_to_ceiling(home->sectors[entity->sector_idx], &new_loc))
	// 	return (FALSE);
	wall = check_if_crossing(home->sectors[entity->sector_idx], new_loc);
	if (wall)
	{
		if (wall->top.idx >= 0)
		{
			// if (check_y_diff(entity, &new_loc, home->sectors[wall->top.idx]))
			// 	return (FALSE);
			if ((wall->is_door && !wall->is_closed) || !wall->is_door)
			{
				entity->sector_idx = wall->top.idx;
			 	entity->pos = vec3_add(entity->pos, vec3_mul(entity->dir, t * 0.005f));
				return (TRUE);
			}
		}
		else
		{
			printf("hit a wall, need to rotate\n");
			entity->top = rotate_triangle(&entity->top, 180, 'y');
			entity->bot = rotate_triangle(&entity->bot, 180, 'y');
			entity->top.normal = triangle_normal(&entity->top);
			entity->bot.normal = entity->top.normal;
			entity->dir = entity->top.normal;
			printf("new direction: x: %f y: %f z: %f\n", entity->dir.x, entity->dir.y, entity->dir.z);
		}
			return (FALSE); // we hit a wall, turn 90 left or right, or do a 180
	}
	else
	{
		entity->pos = vec3_add(entity->pos, vec3_mul(entity->dir, t * 0.005f));
		// dist = check_distance_to_ground(home->sectors[entity->sector_idx], entity, entity->pos);
		// if (dist < 0 && dist > -plr->height)
		// 	plr->pos.y -= dist;
		// add_motion(&plr->pos, t);
		return (TRUE);
	}
	return (FALSE);
}
