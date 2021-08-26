/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_look.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:17:01 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/24 15:48:20 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	player_look(t_home *home, t_player *plr)
{
	Uint32		i;
	t_xyz		isection;
	t_triangle	tested[2];
	Uint32		entity_hit;

	i = 0;
	entity_hit = 0;
	while (i < home->nbr_of_entities)
	{
		if (home->entity_pool[i]->sector_idx == plr->cur_sector)
		{
			translate_entity(&tested[0], &tested[1], home->entity_pool[i]);
			if (vec3_ray_triangle_intersect(&tested[0],
					plr->pos, plr->look_dir, &isection)
				|| vec3_ray_triangle_intersect(&tested[1],
					plr->pos, plr->look_dir, &isection))
				entity_hit = 1;
			if (entity_hit && get_distance_squared(isection, plr->pos)
				< 6.25f)
			{
				plr->display_object = home->entity_pool[i]->entity_type;
				break ;
			}
		}
		i++;
	}
	if (!entity_hit)
		plr->display_object = 0;
	return (0);
}
