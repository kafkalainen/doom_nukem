/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_static_entities.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 09:50:31 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/28 12:06:31 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	initialize_entity_triangles(t_entity *entity)
{
	entity->top.p[0] = (t_xyz){0.0f, 0.0f, 0.0f, 1.0f};
	entity->top.p[1] = (t_xyz){0.0f, 1.0f, 0.0f, 1.0f};
	entity->top.p[2] = (t_xyz){1.0f, 1.0f, 0.0f, 1.0f};
	entity->bot.p[0] = (t_xyz){0.0f, 0.0f, 0.0f, 1.0f};
	entity->bot.p[1] = (t_xyz){1.0f, 1.0f, 0.0f, 1.0f};
	entity->bot.p[2] = (t_xyz){1.0f, 0.0f, 0.0f, 1.0f};
}

void	initialize_entity_movement(t_entity *entity, t_entity_data *data)
{
	if (data->is_static)
		entity->is_static = 1;
	else
		entity->is_static = 0;
	if (entity->is_static)
	{
		if (entity->entity_type == button ||entity->entity_type == powerstation
			|| entity->entity_type == lamp)
		{
		//If entity is static, we can rotate entity towards correct direction.
			entity->velocity = 0;
		// entity->top =
		// entity->bottom =
		}
	}
	else
	{
		if (entity->entity_type == crewmember || entity->entity_type == thing)
			entity->velocity = ENTITY_VELOCITY_1;
		else if (entity->entity_type == skull_skulker || entity->entity_type == drone)
			entity->velocity = ENTITY_VELOCITY_2;
		else
			entity->velocity = 0;
	}
}

t_entity	*new_entity(t_entity_data *data)
{
	t_entity	*entity;

	entity = (t_entity *)malloc(sizeof(entity));
	if (entity)
	{
		initialize_entity_triangles(entity);
		entity->pos = (t_xyz){data->x, data->ground, data->y, 1.0f};
		entity->dir = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
		entity->entity_type = data->entity_type;
		initialize_entity_movement(entity, data);
		initialize_top_texels(&entity->top);
		initialize_bottom_texels(&entity->bot);
	}
	else
	{
		free(entity);
		entity = NULL;
	}
	return (entity);
}
