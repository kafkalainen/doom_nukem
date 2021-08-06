/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_activation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:38:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/06 11:41:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	handle_button(t_entity *entity, t_home *home)
{
	Uint32	i;

	i = 0;
	if (entity->is_linked)
	{
		while (i < home->nbr_of_sectors)
		{
			if (home->sectors[i]->lights.is_linked == entity->is_linked
				&& entity->is_linked > 1)
				break ;
			i++;
		}
	}
	if (entity->state)
		home->sectors[i]->lights.state = 1;
	else
		home->sectors[i]->lights.state = 0;
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

/*
**	Add button type to map data to handle elevators and lights.
**	Lights could have one integer value, and it is affected by the button,
**	or it is not affected by the button, or it is automatically turned on,
**	when player moves to the sector.
**	Lights have idx value matching the entity link index value.
*/
Uint32	handle_activation(t_entity *entity, t_home *home, t_player *plr)
{
	if (entity->entity_type == button)
	{
		if (entity->state)
			entity->state = 0;
		else
			entity->state = 1;
		handle_button(entity, home);
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
