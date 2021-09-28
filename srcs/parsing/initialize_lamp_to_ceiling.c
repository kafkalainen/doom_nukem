/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_lamp_to_ceiling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:11:05 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/28 19:57:41 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	set_lamp_position(t_sector *sector, t_entity *entity,
	t_xyz isection, t_xyz normal)
{
	t_xy	centroid;

	entity->pos.y = isection.y;
	entity->dir = normal;
	if (vec2_eucl_dist(sector->bounding_box.top_left,
			sector->bounding_box.bottom_right) < 1.42f
		|| vec2_eucl_dist(sector->bounding_box.top_left,
			sector->bounding_box.bottom_left) < 1.42f
		|| vec2_eucl_dist(sector->bounding_box.top_right,
			sector->bounding_box.bottom_right) < 1.42f)
	{
		centroid = calculate_centroid(sector);
		entity->pos.x = centroid.x;
		entity->pos.z = centroid.y;
	}
}

void	initialize_lamp_to_ceiling(t_entity *entity, t_home *home)
{
	unsigned int	i;
	t_surface		*ceiling;
	t_xyz			isection;
	t_bool			state;

	i = 0;
	isection = vec3(0, 0, 0);
	entity->pos.y = -99.0f;
	entity->top.normal = (t_xyz){0.0f, -1.0f, 0.0f, 0.0f};
	entity->bot.normal = (t_xyz){0.0f, -1.0f, 0.0f, 0.0f};
	ceiling = home->sectors[entity->sector_idx]->ceiling;
	while (i < home->sectors[entity->sector_idx]->nb_of_ceil)
	{
		state = vec3_ray_triangle_intersect(&ceiling->tri, entity->pos,
				vec3(0.0f, 1.0f, 0.0f), &isection);
		if (state)
			break ;
		ceiling = ceiling->next;
		i++;
	}
	if (state)
		set_lamp_position(home->sectors[entity->sector_idx],
			entity, isection, ceiling->tri.normal);
}
