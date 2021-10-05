/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_on_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 14:53:58 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/05 15:00:29 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	turn_on_lights(t_entity *entity, t_home *home)
{
	if (entity->is_linked > 1)
	{
		if (home->sectors[entity->is_linked - 2] && entity->state)
			home->sectors[entity->is_linked - 2]->lights.state = 1;
		else
			home->sectors[entity->is_linked - 2]->lights.state = 0;
	}
}

void	automatic_lights(t_sector *sector, t_home *home)
{
	t_entity	*entity;

	if (sector->lights.is_linked == 1 && sector->lights.state == 0)
	{
		entity = get_entity_with_sector_and_type(sector->idx_sector,
				lamp, home);
		if (entity != NULL)
			change_texture(entity);
		sector->lights.state = 1;
	}
}
