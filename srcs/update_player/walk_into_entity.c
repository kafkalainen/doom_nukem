/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk_into_entity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:57:16 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/30 18:03:34 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	walking_into_entity(t_xyz plr_pos, int cur_sector,
	t_entity **entities, Uint32 nbr_of_entities)
{
	Uint32	i;

	i = 0;
	while (i < nbr_of_entities && entities[i])
	{
		if (is_enemy(entities[i]->type) && entities[i]->is_active
			&& entities[i]->sector_idx == cur_sector)
		{
			if (get_distance_squared(plr_pos, entities[i]->pos) < 2.0f)
				return (true);
		}
		i++;
	}
	return (false);
}
