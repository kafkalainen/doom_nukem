/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:29:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/27 13:31:44 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	die(t_entity *entity, Uint32 t)
{
	if (entity->health <= 0 && !entity->die_animation)
		entity->die_animation = ENTITY_COOLDOWN_3;
	else if (entity->health <= 0 && entity->die_animation)
	{
		entity->sprite_state = die_now;
		if (entity->anim_offset >= 4
			&& (int)(entity->die_animation - t) < 0)
			entity->is_active = false;
		entity->die_animation = (int)(entity->die_animation - t);
		return (true);
	}
	return (false);
}
