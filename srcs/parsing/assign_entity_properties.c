/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_entity_properties.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 11:27:58 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/13 10:06:42 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
** Issued at assignment of entity properties.
** float		velocity;
** t_triangle	top;
** t_triangle	bot;
** float		height;
** float		width;
** Uint32		take_damage;
** Uint32		cooldown;
** Uint32		is_aggroed;
** int			sprite_index;
** int			alt_sprite_index;
** int			sprite_state;
** int			anim_offset;
** int			health;
** int			ammo;
*/
static void	initialize_entity_triangles(t_entity *entity)
{
	t_xy	size;

	if (entity->entity_type == powerstation
		|| entity->entity_type == crewmember
		|| entity->entity_type == thing)
		size = (t_xy){1.0f, 2.5f};
	else if (entity->entity_type == lamp
		|| entity->entity_type == light_button
		|| entity->entity_type == elevator_button)
		size = (t_xy){0.5f, 0.5f};
	else
		size = (t_xy){1.0f, 1.0f};
	entity->top.p[0] = (t_xyz){0.0f, 0.0f, 0.0f, 1.0f};
	entity->top.p[1] = (t_xyz){0.0f, size.y, 0.0f, 1.0f};
	entity->top.p[2] = (t_xyz){size.x, size.y, 0.0f, 1.0f};
	entity->bot.p[0] = (t_xyz){0.0f, 0.0f, 0.0f, 1.0f};
	entity->bot.p[1] = (t_xyz){size.x, size.y, 0.0f, 1.0f};
	entity->bot.p[2] = (t_xyz){size.x, 0.0f, 0.0f, 1.0f};
	entity->height = size.y;
	entity->legs = size.y * 0.001f;
	entity->width = size.x;
}

static void	initialize_static_entity(t_entity *entity)
{
	if (entity->entity_type == lamp)
	{
		entity->top = rotate_triangle(&entity->top,
				PI_BY_TWO, 'x');
		entity->bot = rotate_triangle(&entity->bot,
				PI_BY_TWO, 'x');
	}
	else
	{
		entity->top = rotate_triangle(&entity->top,
				vec3_angle(entity->top.normal, entity->dir), 'y');
		entity->bot = rotate_triangle(&entity->bot,
				vec3_angle(entity->bot.normal, entity->dir), 'y');
	}
	entity->top.normal = entity->dir;
	entity->bot.normal = entity->dir;
	entity->pos = translate_point(&entity->pos,
			vec3_mul(entity->top.normal, 0.15f));
}

static void	initialize_entity_movement(t_entity *entity)
{
	if (entity->is_static == 1)
	{
		if (entity->entity_type == light_button
			|| entity->entity_type == powerstation
			|| entity->entity_type == lamp
			|| entity->entity_type == elevator_button)
		{
			initialize_static_entity(entity);
			entity->velocity = 0;
		}
	}
	else if (entity->is_static == 0)
	{
		if (entity->entity_type == crewmember || entity->entity_type == thing)
			entity->velocity = ENTITY_VELOCITY_1;
		else if (entity->entity_type == skull_skulker
			|| entity->entity_type == drone)
			entity->velocity = ENTITY_VELOCITY_2;
		else
			entity->velocity = 0;
	}
	else
	{
		error_output("ERROR: Entity has no is_static property.");
	}
}

static void	initialize_entity_values(t_entity *entity, t_xyz plr_pos)
{
	entity->dir = vec3_unit_vector(entity->dir);
	entity->top.normal = (t_xyz){0.0f, 0.0f, -1.0f, 0.0f};
	entity->bot.normal = (t_xyz){0.0f, 0.0f, -1.0f, 0.0f};
	entity->take_damage = 0;
	entity->cooldown = 0;
	entity->is_aggroed = 0;
	entity->sprite_state = 0;
	entity->anim_offset = 0;
	entity->vec_to_plr = vec3_unit_vector(vec3_dec(entity->pos, plr_pos));
	if (entity->entity_type == skull_skulker || entity->entity_type == drone)
		entity->health = 1;
	else if (entity->entity_type == crewmember || entity->entity_type == thing)
		entity->health = 2;
	else
		entity->health = 999;
	entity->ammo = 3;
}

Uint32	assign_entity_properties(t_home *home, t_xyz plr_pos)
{
	Uint32	i;

	i = 0;
	while (i < home->nbr_of_entities)
	{
		initialize_entity_triangles(home->entity_pool[i]);
		initialize_entity_values(home->entity_pool[i], plr_pos);
		initialize_entity_movement(home->entity_pool[i]);
		initialize_entity_textures(home->entity_pool[i]);
		i++;
	}
	return (0);
}
