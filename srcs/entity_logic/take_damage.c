/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_damage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:19:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/29 19:08:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	take_damage(t_entity *entity, Uint32 t)
{
	(void)t;
	if (entity->take_damage == true)
	{
		if (entity->is_aggroed == true)
			entity->sprite_state = in_front;
		entity->anim_offset = 5;
		entity->health--;
		entity->take_damage = false;
		return (true);
	}
	return (false);
}
