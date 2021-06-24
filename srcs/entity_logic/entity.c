/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:31:48 by rzukale           #+#    #+#             */
/*   Updated: 2021/06/24 14:52:10 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	check_aggro(t_player *plr, t_entity *entity, t_sector *sector)
{
	float			distance_squared;
	Uint32			signed_dst;
	unsigned int	i;
	t_wall			*wall;

	distance_squared = 0;
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
