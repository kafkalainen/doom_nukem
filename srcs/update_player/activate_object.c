/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activate_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:18:48 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/06 20:45:33 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_entity	*activate_object(t_home *home, t_player *plr)
{
	Uint32		i;
	t_xyz		isection;
	t_triangle	tested[2];
	Uint32		entity_hit;

	i = 0;
	entity_hit = 0;
	while (i < home->nbr_of_entities)
	{
		if (home->entity_pool[i]->sector_idx == plr->cur_sector
			&& home->entity_pool[i]->is_active == true)
		{
			translate_entity(&tested[0], &tested[1], home->entity_pool[i]);
			if (vec3_ray_triangle_intersect(&tested[0],
					plr->pos, plr->look_dir, &isection)
				|| vec3_ray_triangle_intersect(&tested[1],
					plr->pos, plr->look_dir, &isection))
				entity_hit = 1;
			if (entity_hit && vec3_eucl_dist(vec3_dec(isection, plr->pos))
				< 2.5f)
				return (home->entity_pool[i]);
		}
		i++;
	}
	return (NULL);
}
