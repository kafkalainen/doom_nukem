/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_aggro.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 13:14:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/24 14:08:36 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	check_for_close_range(Uint32 signed_dst, float distance_squared,
	t_player *plr, t_entity *entity)
{
	if (distance_squared <= AGGRO_RANGE_1
		&& signed_dst == 0
		&& plr->cur_sector == entity->sector_idx)
	{
		entity->is_aggroed = 1;
		return (1);
	}
	return (0);
}

Uint32	check_if_in_next_sector(t_sector *sector, float distance_squared,
	t_player *plr, t_entity *entity)
{
	unsigned int	i;
	t_wall			*wall;
	Uint32			signed_dst;
	t_xyz			vec_to_plr;
	t_xyz			isection;

	i = 0;
	wall = sector->walls;
	signed_dst = vec3_signed_distance_to_plane(plr->pos, entity->dir,
			entity->pos);
	vec_to_plr = vec3_unit_vector(vec3_dec(plr->pos, entity->pos));
	if (distance_squared <= AGGRO_RANGE_1
		&& signed_dst == 0 && plr->cur_sector != entity->sector_idx)
	{
		while (i < sector->nb_of_walls)
		{
			if (check_if_portal(wall)
				&& ((wall->is_door && !wall->is_closed) || !wall->is_door))
			{
				if (vec3_ray_triangle_intersect(&wall->top, entity->pos, vec_to_plr, &isection)
					|| vec3_ray_triangle_intersect(&wall->bottom, entity->pos, vec_to_plr, &isection))
				{
					entity->is_aggroed = 1;
					return (1);
				}
			}
			i++;
			wall = wall->next;
		}
	}
	return (0);
}

Uint32	check_aggro(t_player *plr, t_entity *entity, t_sector *sector)
{
	float			distance_squared;
	Uint32			signed_dst;

	distance_squared = get_distance_squared(entity->pos, plr->pos);
	signed_dst = vec3_signed_distance_to_plane(plr->pos, entity->dir,
			entity->pos);
	if (check_for_close_range(signed_dst, distance_squared, plr, entity))
		return (TRUE);
	if (check_if_in_next_sector(sector, distance_squared, plr,
			entity))
		return (TRUE);
	if (distance_squared <= 1)
	{
		entity->is_aggroed = 1;
		return (TRUE);
	}
	return (FALSE);
}
