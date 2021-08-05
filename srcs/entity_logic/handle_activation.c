/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_activation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:38:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/05 16:05:51 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	handle_button(t_entity *entity, t_sector *sector)
{
	if (entity->state)
		sector->lights.state = 1;
	else
		sector->lights.state = 0;
}

static void	change_texture(t_entity *entity)
{
	if (entity->state)
	{
		entity->top.idx = entity->sprite_index;
		entity->bot.idx = entity->sprite_index;
	}
	else
	{
		entity->top.idx = entity->alt_sprite_index;
		entity->bot.idx = entity->alt_sprite_index;
	}
}

Uint32	handle_activation(t_entity *entity, t_sector *sector, t_player *plr)
{
	if (entity->entity_type == button)
	{
		if (entity->state)
			entity->state = 0;
		else
			entity->state = 1;
		handle_button(entity, sector);
	}
	if (entity->entity_type == powerstation)
	{
		if (entity->state)
		{
			entity->state = 0;
			if (plr->power_points < 5)
				plr->power_points += 3;
		}
	}
	change_texture(entity);
	return (1);
}
