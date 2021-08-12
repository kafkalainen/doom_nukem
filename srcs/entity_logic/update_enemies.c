/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:36:37 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/12 14:03:44 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	update_enemies(t_home *home, t_player *plr, Uint32 delta_time)
{
	(void)delta_time;
	Uint32	i;

	i = 0;
	while (i < home->nbr_of_entities)
	{
		if (home->entity_pool[i]->entity_type != ENTITY_DEAD)
		{
			if (home->entity_pool[i]->entity_type == skull_skulker
				|| home->entity_pool[i]->entity_type == thing)
			{
				determine_angle_between_entity_and_plr(home->entity_pool[i], plr);
				set_entity_texels_for_frame(home->entity_pool[i]);
			}
		}
		i++;
	}

}
