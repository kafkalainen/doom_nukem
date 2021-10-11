/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_poster_hit_point.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:44:29 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/11 14:48:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float	get_poster_hit_point(t_home *home, t_ray *ray, t_bullet_hole *hole,
		int bullet_sector)
{
	t_uint		i;
	t_triangle	tested[2];
	float		distance;

	i = 0;
	distance = 400000000.0f;
	hole->type = nothing;
	while (i < home->nbr_of_entities)
	{
		if (home->entity_pool[i]->type == poster
			&& home->entity_pool[i]->sector_idx == bullet_sector)
		{
			translate_entity(&tested[0], &tested[1], home->entity_pool[i]);
			if (test_ray(&tested[0], hole, &distance, ray)
				|| test_ray(&tested[1], hole, &distance, ray))
			{
				ft_putendl("hit poster");
				hole->type = nothing;
				hole->sector_idx = bullet_sector;
				home->entity_pool[i]->health--;
			}
		}
		i++;
	}
	return (distance);
}
