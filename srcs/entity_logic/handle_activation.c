/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_activation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:38:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/09 11:37:49 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	handle_button(t_entity *entity, t_home *home, t_player *plr)
{
	if (entity->type == light_button)
		turn_on_lights(entity, home);
	else if (entity->type == lift_button)
		activate_lift(home, entity, plr);
	else
		return ;
	play_sound(plr->audio.button, 20);
}

static void	change_texture(t_entity *entity)
{
	if (entity->state)
	{
		entity->top.type = entity->sprite_index;
		entity->bot.type = entity->sprite_index;
	}
	else
	{
		entity->top.type = entity->alt_sprite_index;
		entity->bot.type = entity->alt_sprite_index;
	}
}

t_bool	activate_power_station(t_entity *power_station, t_player *plr)
{
	if (power_station->state)
	{
		power_station->state = 0;
		plr->recharge = 1000;
		play_sound(plr->audio.recharge, 30);
		return (true);
	}
	play_sound(plr->audio.power_station_depleted, 30);
	return (false);
}

t_bool	pick_up_item(t_entity *item, t_player *plr)
{
	int	i;

	i = 0;
	while (plr->inventory[i].in_use)
		i++;
	if (i >= 4)
		return (false);
	plr->inventory[i].in_use = true;
	plr->inventory[i].sprite_idx = -item->sprite_index;
	item->is_active = false;
	return (true);
}

/*
**	Add sound handle to activate powerstation
*/
t_bool	handle_activation(t_entity *entity, t_home *home, t_player *plr)
{
	if (entity->type == light_button
		|| entity->type == lift_button)
	{
		if (entity->state)
			entity->state = 0;
		else
			entity->state = 1;
		handle_button(entity, home, plr);
	}
	else if (entity->type == powerstation)
		activate_power_station(entity, plr);
	else if (entity->type >= ammo_pack
		&& entity->type <= keycard_military)
		pick_up_item(entity, plr);
	else
		return (0);
	change_texture(entity);
	return (1);
}
