/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_damage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:19:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/24 15:37:26 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	take_damage(t_entity *entity, Uint32 t)
{
	if (entity->take_damage == TRUE && entity->cooldown > 0)
	{
		if (entity->health > 0)
		{
			if (entity->is_aggroed == TRUE)
				entity->sprite_state = in_front;
			entity->cooldown = entity->cooldown - t;
			entity->anim_offset = 5;
			if (entity->cooldown < 0)
			{
				entity->take_damage = FALSE;
				entity->health--;
			}
		}
		return (TRUE);
	}
	return (FALSE);
}
