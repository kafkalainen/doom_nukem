/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_lamp_to_ceiling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:11:05 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/06 19:01:22 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	set_lamp_position(t_sector *sector, t_entity *entity,
	t_xyz isection, t_xyz normal)
{
	entity->dir = normal;
	entity->pos.x = sector->centroid.x;
	entity->pos.y = isection.y;
	entity->pos.z = sector->centroid.y;
}

static void	init_lamp_values(unsigned int *i, t_xyz *isection, float *pos_y)
{
	*i = 0;
	*isection = vec3(0, 0, 0);
	*pos_y = -99.0f;
}

void	initialize_lamp_to_ceiling(t_entity *entity, t_home *home)
{
	unsigned int	i;
	t_surface		*ceiling;
	t_xyz			isection;
	t_bool			state;

	init_lamp_values(&i, &isection, &entity->pos.y);
	entity->top.normal = (t_xyz){0.0f, -1.0f, 0.0f, 0.0f};
	entity->bot.normal = (t_xyz){0.0f, -1.0f, 0.0f, 0.0f};
	ceiling = home->sectors[entity->sector_idx]->ceiling;
	state = false;
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
	{
		set_lamp_position(home->sectors[entity->sector_idx],
			entity, isection, ceiling->tri.normal);
	}
}
