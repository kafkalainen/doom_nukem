/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_noise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:11:42 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/06 21:15:14 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	make_noise(t_entity *entity, t_player *plr, Uint32 t)
{
	float	dist;

	if (entity->making_noise <= 0)
	{
		dist = get_distance_squared(plr->pos, entity->pos);
		if (dist >= 49.0f || dist <= 1.0f)
			return ;
		entity->making_noise = 5000;
		if (dist <= 49.0f && dist > 36.0f)
			dist = 40;
		else if (dist <= 36.0f && dist > 25.0f)
			dist = 30;
		else if (dist <= 25.0f && dist > 16.0f)
			dist = 25;
		else if (dist <= 16.0f && dist > 9.0f)
			dist = 20;
		else if (dist <= 9.0f && dist > 4.0f)
			dist = 15;
		else if (dist <= 4.0f && dist > 1.0f)
			dist = 10;
		if (entity->type == skull_skulker)
			play_sound(plr->audio.skull_skulker_lulling, dist);
		else
			play_sound(plr->audio.thing_lulling, dist);
	}
	else
		entity->making_noise -= t;
}
