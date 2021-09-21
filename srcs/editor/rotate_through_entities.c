/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_through_entities.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:22:07 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/21 09:19:22 by rzukale          ###   ########.fr       */
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
	if (entity->entity_type == skull_skulker)
		entity->entity_type = thing;
	else if (entity->entity_type == thing)
		entity->entity_type = drone;
	else if (entity->entity_type == drone)
		entity->entity_type = crewmember;
	else if (entity->entity_type == crewmember)
		entity->entity_type = ammo_pack;
	else if (entity->entity_type == ammo_pack)
		entity->entity_type = keycard_cleaning;
	else if (entity->entity_type == keycard_cleaning)
		entity->entity_type = keycard_engineering;
	else if (entity->entity_type == keycard_engineering)
		entity->entity_type = keycard_military;
	else if (entity->entity_type == keycard_military)
		entity->entity_type = skull_skulker;
	if (entity->entity_type == skull_skulker || entity->entity_type == thing
		|| entity->entity_type == drone || entity->entity_type == crewmember)
		init_non_static_entity_values(entity);
	else if (entity->entity_type == ammo_pack || entity->entity_type == keycard_cleaning
		|| entity->entity_type == keycard_engineering || entity->entity_type == keycard_military)
		init_static_entity_values(entity);
	action->change_entity_type = 0;
}
