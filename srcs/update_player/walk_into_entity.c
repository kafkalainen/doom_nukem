/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk_into_entity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:57:16 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/05 13:41:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_entity	*walking_into_entity(t_xyz plr_pos, int cur_sector,
	t_entity **entities, Uint32 nbr_of_entities)
{
	Uint32	i;

	i = 0;
	while (i < nbr_of_entities && entities[i])
	{
		if (is_enemy(entities[i]->type) && entities[i]->is_active
			&& entities[i]->sector_idx == cur_sector)
		{
			if (get_distance_squared(plr_pos, entities[i]->pos) < MIN_DAM_DIST)
			{
				entities[i]->is_aggroed = true;
				entities[i]->velocity = 0.0025f;
				return (entities[i]);
			}
		}
		i++;
	}
	return (NULL);
}
