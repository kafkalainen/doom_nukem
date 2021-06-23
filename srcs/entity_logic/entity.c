/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:31:48 by rzukale           #+#    #+#             */
/*   Updated: 2021/06/23 16:24:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	check_aggro(t_xyz plr_pos, t_entity *entity)
{
	float	distance_squared;

	distance_squared = 0;
	// if (entity->entity_type == 1)
	// 	distance_squared = AGGRO_RANGE_1 * AGGRO_RANGE_1;
	// else
	// 	distance_squared = AGGRO_RANGE_2 * AGGRO_RANGE_2;
	distance_squared = ((plr_pos.x - entity->pos.x) * (plr_pos.x - entity->pos.x) +
		(plr_pos.y - entity->pos.y) * (plr_pos.y - entity->pos.y) +
		(plr_pos.z - entity->pos.z) * (plr_pos.z - entity->pos.z));
	// printf("squared distance between entity and player is: %f\n", distance_squared);
	if (distance_squared <= AGGRO_RANGE_1) // check to see if we can see the player
		entity->is_aggroed = 1;
}
