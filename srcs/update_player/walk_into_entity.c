/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk_into_entity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:57:16 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/07 09:28:01 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_entity	*walking_into_entity(t_xyz test, t_player *plr,
			t_entity **entities, Uint32 nbr_of_entities)
{
	Uint32	i;

	i = 0;
	test = vec3(test.x, test.y - plr->height, test.z);
	while (i < nbr_of_entities && entities[i])
	{
		if (is_enemy(entities[i]->type) && entities[i]->is_active
			&& entities[i]->sector_idx == plr->cur_sector)
		{
			if (get_distance_squared(test, entities[i]->pos) < MIN_DAM_DIST)
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
