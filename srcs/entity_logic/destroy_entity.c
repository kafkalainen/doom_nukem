/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_entity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:18:09 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/11 14:20:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	destroy_entity(t_entity *entity)
{
	if (entity->health <= 0 && entity->is_static)
	{
		entity->top.type = entity->alt_sprite_index;
		entity->bot.type = entity->alt_sprite_index;
	}
}
