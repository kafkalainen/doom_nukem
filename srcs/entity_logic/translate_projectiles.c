/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_projectiles.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:08:55 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/28 11:15:39 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	translate_projectiles(t_home *home, float distance, int sector_idx)
{
	t_uint	i;
	t_xyz	translation;

	i = 0;
	translation = (t_xyz){0.0f, distance, 0.0f, 0.0f};
	while (i < home->nbr_of_projectiles)
	{
		if (home->projectile_pool[i]->sector_idx == sector_idx
			&& !home->projectile_pool[i]->is_active
			&& home->projectile_pool[i]->top.type == -bullet_decal)
		{
			home->projectile_pool[i]->pos
				= vec3_add(home->projectile_pool[i]->pos, translation);
		}
		i++;
	}
}
