/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_look.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:17:01 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/04 15:55:32 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	player_look(t_home *home, t_player *plr)
{
	Uint32		i;
	t_xyz		isection;
	t_triangle	tested[2];

	i = 0;
	while (i < home->nbr_of_entities)
	{
		if (home->entity_pool[i]->sector_idx == plr->cur_sector)
		{
			tested[0] = translate_triangle(&home->entity_pool[i]->top,
				home->entity_pool[i]->pos);
			tested[1] = translate_triangle(&home->entity_pool[i]->bot,
				home->entity_pool[i]->pos);
			tested[0].normal = triangle_normal(&tested[0]);
			tested[1].normal = triangle_normal(&tested[1]);
			if (vec3_ray_triangle_intersect(&tested[0],
				plr->pos, plr->look_dir, &isection))
				ft_putendl("THERE's SMOTHING.");
			if (vec3_ray_triangle_intersect(&tested[1],
				plr->pos, plr->look_dir, &isection))
				ft_putendl("THERE's SMOTHING.");
		}
		i++;
	}
	return (0);
}
