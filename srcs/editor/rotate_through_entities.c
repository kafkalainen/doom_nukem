/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_through_entities.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:22:07 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/07 11:55:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	init_static_entity_values(t_entity_list *entity)
{
	entity->is_static = true;
	entity->state = true;
}

static void	init_non_static_entity_values(t_entity_list *entity)
{
	entity->is_static = false;
	entity->is_linked = false;
	entity->state = false;
}

void	rotate_through_entities(t_entity_list *entity, t_action *action)
{
	if (entity->type == skull_skulker)
		entity->type = thing;
	else if (entity->type == thing)
		entity->type = ammo_pack;
	else if (entity->type == ammo_pack)
		entity->type = keycard_cleaning;
	else if (entity->type == keycard_cleaning)
		entity->type = keycard_engineering;
	else if (entity->type == keycard_engineering)
		entity->type = keycard_military;
	else if (entity->type == keycard_military)
		entity->type = skull_skulker;
	if (entity->type == skull_skulker || entity->type == thing
		|| entity->type == drone || entity->type == crewmember)
		init_non_static_entity_values(entity);
	else if (entity->type == ammo_pack
		|| entity->type == keycard_cleaning
		|| entity->type == keycard_engineering
		|| entity->type == keycard_military)
		init_static_entity_values(entity);
	action->change_entity_type = false;
}
