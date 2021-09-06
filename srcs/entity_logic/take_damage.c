/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_damage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:19:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/05 23:07:38 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	take_damage(t_entity *entity, Uint32 t)
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
				return (true);
			}
		}
	}
	return (false);
}
