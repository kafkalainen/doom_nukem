/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:31:48 by rzukale           #+#    #+#             */
/*   Updated: 2021/06/23 16:46:46 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	check_aggro(t_xyz plr_pos, t_entity *entity)
{
	float	distance_squared;

	distance_squared = 0;
	distance_squared = ((plr_pos.x - entity->pos.x) * (plr_pos.x - entity->pos.x) +
		(plr_pos.y - entity->pos.y) * (plr_pos.y - entity->pos.y) +
		(plr_pos.z - entity->pos.z) * (plr_pos.z - entity->pos.z));
	if (distance_squared <= AGGRO_RANGE_1)
	{
		entity->is_aggroed = 1;
		return (1);
	}
	return (0);
}
