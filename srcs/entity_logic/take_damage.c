/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_damage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:19:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/20 10:48:00 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	take_damage(t_entity *entity)
{
	if (entity->take_damage == TRUE)
	{
		if (entity->health > 0)
		{
			entity->anim_offset = 5;
			entity->take_damage = FALSE;
			entity->health--;
		}
		return (TRUE);
	}
	return (FALSE);
}
