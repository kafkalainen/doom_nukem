/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_damage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:19:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/01 10:52:30 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	take_damage(t_entity *entity, Uint32 t)
{
	if (entity->taking_damage > 0)
	{
		if (entity->sprite_state == attack)
			entity->sprite_state = in_front;
		entity->anim_offset = 5;
		entity->taking_damage -= t;
		if (entity->taking_damage <= 0)
		{
			entity->health--;
			return (true);
		}
	}
	return (false);
}
