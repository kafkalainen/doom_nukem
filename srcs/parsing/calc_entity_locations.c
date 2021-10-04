/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_entity_locations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:38:25 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/04 16:30:00 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	calc_entity_locations(t_home *home)
{
	Uint32		i;
	t_sector	*temp_sector;
	t_entity	*temp;

	i = 0;
	while (i < home->nbr_of_entities)
	{
		temp = home->entity_pool[i];
		if (is_enemy(temp->type)
			|| temp->type == ammo_pack || temp->type == keycard_cleaning
			|| temp->type == keycard_engineering
			|| temp->type == keycard_military)
		{
			temp_sector = home->sectors[temp->sector_idx];
			if (temp->pos.x == temp_sector->bounding_box.top_left.x)
				temp->pos.x += 0.5f;
			else
				temp->pos.x -= 0.5f;
			if (temp->pos.z == temp_sector->bounding_box.top_left.y)
				temp->pos.z += 0.5f;
			else
				temp->pos.z -= 0.5f;
		}
		i++;
	}
}
