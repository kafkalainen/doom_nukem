/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_activation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:38:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/02 13:38:59 by jnivala          ###   ########.fr       */
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

t_bool	activate_power_station(t_entity *power_station, t_player *plr)
{
	if (power_station->state)
	{
		power_station->state = 0;
		if (plr->power_points < 5)
			plr->power_points += 3;
		return (true);
	}
	return (false);
}

/*
**	We need to render ammo packs that haven't been picked up.
**	Basically we can use entity->state. If true, ammopack is in the world,
**	if false, ammo pack has been picked up.
*/
t_bool	pick_up_ammo_pack(t_entity *ammo_pack, t_player *plr)
{
	int	i;

	i = 0;
	while (plr->inventory[i].in_use)
		i++;
	if (i >= 4)
		return (false);
	plr->inventory[i].in_use = true;
	plr->inventory[i].sprite_idx = ammo_pack_sprite;
	ammo_pack->is_active = false;
	return (true);
}

/*
**	Add sound handle to activate powerstation
*/
t_bool	handle_activation(t_entity *entity, t_home *home, t_player *plr)
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
		activate_power_station(entity, plr);
	else if (entity->entity_type == ammo_pack)
		pick_up_ammo_pack(entity, plr);
	else
		return (0);
	change_texture(entity);
	return (1);
}
