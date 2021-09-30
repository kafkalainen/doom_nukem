/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_entity_properties.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 11:27:58 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/30 15:28:03 by jnivala          ###   ########.fr       */
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

static void	initialize_moving_entity(t_entity *current)
{
	float	angle[3];
	t_m4x4	y;
	t_m4x4	combined;

	angle[1] = vec3_ang_axis(current->top.normal, current->vec_to_plr, 'y');
	y = rotation_matrix_y(angle[1]);
	combined = y;
	current->top.p[0] = multi_vec_matrix(&current->top.p[0], &combined);
	current->top.p[1] = multi_vec_matrix(&current->top.p[1], &combined);
	current->top.p[2] = multi_vec_matrix(&current->top.p[2], &combined);
	current->bot.p[0] = multi_vec_matrix(&current->bot.p[0], &combined);
	current->bot.p[1] = multi_vec_matrix(&current->bot.p[1], &combined);
	current->bot.p[2] = multi_vec_matrix(&current->bot.p[2], &combined);
	current->top.normal = current->vec_to_plr;
	current->bot.normal = current->vec_to_plr;
}

static void	initialize_entity_movement(t_entity *entity, t_home *home)
{
	if (entity->is_static == true)
	{
		if (entity->type >= light_button
			&& entity->type <= keycard_military)
		{
			if (entity->type == lamp)
				initialize_lamp_to_ceiling(entity, home);
			initialize_static_entity(entity);
			entity->velocity = 0;
		}
	}
	else if (entity->is_static == false)
	{
		if (entity->type == crewmember || entity->type == thing)
			entity->velocity = ENTITY_VELOCITY_1;
		else if (entity->type == skull_skulker
			|| entity->type == drone)
			entity->velocity = ENTITY_VELOCITY_2;
		else
			entity->velocity = 0;
		initialize_moving_entity(entity);
	}
}

static void	initialize_entity_values(t_entity *entity, t_xyz plr_pos)
{
	entity->dir = vec3_unit_vector(entity->dir);
	entity->top.normal = (t_xyz){0.0f, 0.0f, -1.0f, 0.0f};
	entity->bot.normal = (t_xyz){0.0f, 0.0f, -1.0f, 0.0f};
	entity->take_damage = false;
	entity->cooldown = 0;
	entity->making_noise = 0;
	entity->die_animation = 0;
	entity->is_aggroed = false;
	entity->sprite_state = 0;
	entity->anim_offset = 0;
	entity->falling = 0;
	entity->vec_to_plr_2d = vec2_unit_vector(vec2_dec(vec3_to_vec2(plr_pos),
				vec3_to_vec2(entity->pos)));
	entity->vec_to_plr = vec3_unit_vector(vec3_dec(plr_pos, entity->pos));
	if (entity->type == skull_skulker || entity->type == drone)
		entity->health = 2;
	else if (entity->type == crewmember || entity->type == thing)
		entity->health = 3;
	else
		entity->health = 999;
	if (entity->type >= ammo_pack && entity->type <= keycard_military)
		entity->is_pickupable = true;
	else
		entity->is_pickupable = false;
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
		initialize_entity_movement(home->entity_pool[i], home);
		initialize_entity_textures(home->entity_pool[i]);
		i++;
	}
	return (0);
}
