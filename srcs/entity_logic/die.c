/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:29:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/29 18:10:39 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	die(t_entity *entity, Uint32 t)
{
	if (entity->health <= 0 && entity->sprite_state != die_now)
	{
		entity->sprite_state = die_now;
		entity->cooldown = MOVE_COOLDOWN;
		entity->anim_offset = ENTITY_SPRITE_MOVE_START;
		return (true);
	}
	if (entity->health <= 0 && entity->sprite_state == die_now)
		pick_next_frame(entity, t, MOVE_COOLDOWN);
	if (entity->anim_offset >= 4 && entity->sprite_state == die_now)
		entity->is_active = false;
	return (false);
}
