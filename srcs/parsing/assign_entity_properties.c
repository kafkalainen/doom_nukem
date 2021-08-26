/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_entity_properties.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 11:27:58 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/25 11:30:49 by jnivala          ###   ########.fr       */
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
		size = (t_xy){2.0f, 2.0f};
	else if (entity->entity_type == lamp
		|| entity->entity_type == light_button
		|| entity->entity_type == elevator_button)
		size = (t_xy){0.5f, 0.5f};
	else
		size = (t_xy){1.0f, 1.0f};
	entity->top.p[0] = (t_xyz){-0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
	entity->top.p[1] = (t_xyz){-0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
	entity->top.p[2] = (t_xyz){0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
	entity->bot.p[0] = (t_xyz){-0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
	entity->bot.p[1] = (t_xyz){0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
	entity->bot.p[2] = (t_xyz){0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
	entity->height = size.y;
	entity->legs = size.y * 0.3f;
	entity->width = size.x;
}

static void	initialize_static_entity(t_entity *current)
{
	float	angle[3];
	t_m4x4	x;
	t_m4x4	y;
	t_m4x4	z;
	t_m4x4	combined;

	angle[0] = vec3_ang_axis(current->top.normal, current->dir, 'x');
	angle[1] = vec3_ang_axis(current->top.normal, current->dir, 'y');
	angle[2] = vec3_ang_axis(current->top.normal, current->dir, 'z');
	x = rotation_matrix_x(angle[0]);
	y = rotation_matrix_y(angle[1]);
	z = rotation_matrix_z(angle[2]);
	combined = multiply_matrix(&z, &y);
	combined = multiply_matrix(&combined, &x);
	current->top.p[0] = multi_vec_matrix(&current->top.p[0], &combined);
	current->top.p[1] = multi_vec_matrix(&current->top.p[1], &combined);
	current->top.p[2] = multi_vec_matrix(&current->top.p[2], &combined);
	current->bot.p[0] = multi_vec_matrix(&current->bot.p[0], &combined);
	current->bot.p[1] = multi_vec_matrix(&current->bot.p[1], &combined);
	current->bot.p[2] = multi_vec_matrix(&current->bot.p[2], &combined);
	current->top.normal = current->dir;
	current->bot.normal = current->dir;
	current->pos = translate_point(&current->pos,
			vec3_mul(current->top.normal, 0.15f));
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
	entity->time = 0;
	entity->vec_to_plr = vec2_norm(vec2_dec(vec3_to_vec2(plr_pos),
				vec3_to_vec2(entity->pos)));
	if (entity->entity_type == skull_skulker || entity->entity_type == drone)
		entity->health = 2;
	else if (entity->entity_type == crewmember || entity->entity_type == thing)
		entity->health = 3;
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
