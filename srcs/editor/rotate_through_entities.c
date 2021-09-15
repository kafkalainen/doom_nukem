/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_through_entities.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:22:07 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 10:23:10 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

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
		action->change_entity_type = 0;
}
