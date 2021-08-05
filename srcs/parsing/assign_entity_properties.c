/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_entity_properties.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 11:27:58 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/05 11:51:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

//Issued later.
// float		velocity; // can be looked up via macros
// t_triangle	top; // calculated per frame
// t_triangle	bot; // calculated per frame
// Uint32		take_damage; // boolean to see if we took damage this tick
// Uint32		cooldown; // wait time between moving between idle and move states, or cooldown between attacks
// Uint32		is_aggroed; // default false, based on distance between entity and player, if within distance parameters, cast ray to see if we can see enemy
// 						// if true, aggro = true
// int			sprite_index; // determined by entity_type // ALWAYS >= 0 // what sprite texture are we drawing from
// int			alt_sprite_index; // default = 0
// int			sprite_state; // angle between player and entity determines X axis of sprite map
// int			anim_offset; // determines Y axis of sprite map
// int			health; // 1 or 2 // determined by entity_type
// int			ammo; // defaults to 3

static void	initialize_entity_triangles(t_entity *entity)
{
	t_xy	size;

	if (entity->entity_type == powerstation
		|| entity->entity_type == crewmember
		|| entity->entity_type == thing)
		size = (t_xy){1.0f, 2.5f};
	else if (entity->entity_type == lamp
		|| entity->entity_type == button)
		size = (t_xy){0.5f, 0.5f};
	else
		size = (t_xy){1.0f, 1.0f};
	entity->top.p[0] = (t_xyz){0.0f, 0.0f, 0.0f, 1.0f};
	entity->top.p[1] = (t_xyz){size.x, size.y, 0.0f, 1.0f};
	entity->top.p[2] = (t_xyz){0.0f, size.y, 0.0f, 1.0f};
	entity->bot.p[0] = (t_xyz){0.0f, 0.0f, 0.0f, 1.0f};
	entity->bot.p[1] = (t_xyz){size.x, 0.0f, 0.0f, 1.0f};
	entity->bot.p[2] = (t_xyz){size.x, size.y, 0.0f, 1.0f};
}

static void	initialize_static_entity(t_entity *entity)
{
	entity->top = rotate_triangle(&entity->top,
		-vec3_angle(entity->dir, entity->top.normal), 'y');
	entity->bot = rotate_triangle(&entity->bot,
		-vec3_angle(entity->dir, entity->top.normal), 'y');
	entity->top.normal = entity->dir;
	entity->bot.normal = entity->dir;
	entity->pos = translate_point(&entity->pos,
		vec3_mul(entity->dir, 0.15f));
}

static void	initialize_entity_movement(t_entity *entity)
{
	if (entity->is_static == 1)
	{
		if (entity->entity_type == button ||entity->entity_type == powerstation
			|| entity->entity_type == lamp)
		{
			initialize_static_entity(entity);
			entity->velocity = 0;
		}
	}
	else if (entity->is_static == 0)
	{
		if (entity->entity_type == crewmember || entity->entity_type == thing)
			entity->velocity = ENTITY_VELOCITY_1;
		else if (entity->entity_type == skull_skulker || entity->entity_type == drone)
			entity->velocity = ENTITY_VELOCITY_2;
		else
			entity->velocity = 0;
	}
	else
	{
		error_output("ERROR: Entity has no is_static property.");
	}
}

static void	initialize_entity_values(t_entity *entity)
{
	entity->dir = vec3_unit_vector(entity->dir);
	entity->top.normal = (t_xyz){0.0f, 0.0f, 1.0f, 0.0f};
	entity->bot.normal = (t_xyz){0.0f, 0.0f, 1.0f, 0.0f};
	entity->take_damage = 0;
	entity->cooldown = 0;
	entity->is_aggroed = 0;
	entity->sprite_state = 0;
	entity->anim_offset = 0;
	if (entity->entity_type == skull_skulker || entity->entity_type == drone)
		entity->health = 1;
	else if (entity->entity_type == crewmember || entity->entity_type == thing)
		entity->health = 2;
	else
		entity->health = 999;
	entity->ammo = 3;
}

Uint32		assign_entity_properties(t_home *home)
{
	Uint32	i;

	i = 0;
	while (i < home->nbr_of_entities)
	{
		initialize_entity_triangles(home->entity_pool[i]);
		initialize_entity_values(home->entity_pool[i]);
		initialize_entity_movement(home->entity_pool[i]);
		initialize_entity_textures(home->entity_pool[i]);
		i++;
	}
	return (0);
}
