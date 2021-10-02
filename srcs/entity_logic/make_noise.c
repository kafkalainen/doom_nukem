/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_noise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:11:42 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/02 16:53:32 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	make_noise(t_entity *entity, t_player *plr, Uint32 t)
{
	float	dist;

	if (entity->making_noise <= 0)
	{
		entity->making_noise = 5000;
		dist = get_distance_squared(plr->pos, entity->pos);
		if (dist)
			dist = 1 / dist * 200;
		else
			dist = 30;
		if (entity->type == skull_skulker)
			play_sound(plr->audio.skull_skulker_lulling, ft_imin(60, dist));
		else
			play_sound(plr->audio.thing_lulling, ft_imin(60, dist));
	}
	else
		entity->making_noise -= t;
}
