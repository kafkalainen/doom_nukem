/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_activation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:38:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/24 09:06:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	handle_button(t_entity *entity, t_home *home, t_player *plr)
{
	if (entity->entity_type == light_button)
		turn_on_lights(entity, home);
	else if (entity->entity_type == elevator_button)
		activate_elevator(home, entity, plr);
	else
		return ;
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

Uint32	handle_activation(t_entity *entity, t_home *home, t_player *plr)
{
	if (entity->entity_type == light_button
		|| entity->entity_type == elevator_button)
	{
		if (entity->state)
			entity->state = 0;
		else
			entity->state = 1;
		handle_button(entity, home, plr);
	}
	else if (entity->entity_type == powerstation)
	{
		if (entity->state)
		{
			entity->state = 0;
			if (plr->power_points < 5)
				plr->power_points += 3;
		}
	}
	else
		return (0);
	change_texture(entity);
	return (1);
}
