/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:29:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/20 10:50:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	die(t_entity *entity, Uint32 t)
{
	if (entity->health <= 0)
	{
		printf("I DIE!\n");
		entity->sprite_state = die_now;
		pick_next_frame(entity, t);
		if (entity->anim_offset == 4)
			entity->is_active = FALSE;
		return (TRUE);
	}
	return (FALSE);
}
