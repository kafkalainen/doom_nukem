/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_entity_hit_point.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 09:27:48 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/30 13:46:16 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float	get_entity_hit_point(t_home *home, t_ray *ray, t_bullet_hole *hole,
		int bullet_sector)
{
	Uint32		i;
	t_triangle	tested[2];
	float		distance;

	i = 0;
	distance = 400000000.0f;
	hole->hole_type = nothing;
	while (i < home->nbr_of_entities)
	{
		if (home->entity_pool[i]->is_active
			&& home->entity_pool[i]->sector_idx == bullet_sector)
		{
			translate_entity(&tested[0], &tested[1], home->entity_pool[i]);
			if (test_ray(&tested[0], hole, &distance, ray)
				|| test_ray(&tested[1], hole, &distance, ray))
			{
				hole->hole_type = nothing;
				hole->sector_idx = bullet_sector;
				home->entity_pool[i]->take_damage = true;
				home->entity_pool[i]->is_aggroed = true;
			}
		}
		i++;
	}
	return (distance);
}
