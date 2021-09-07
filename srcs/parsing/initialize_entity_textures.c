/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_entity_textures.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 12:21:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 16:55:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	initialize_static_entity(t_entity *entity)
{
	if (entity->type == lift_button || entity->type == light_button)
	{
		entity->sprite_index = -button_on;
		entity->alt_sprite_index = -button_off;
	}
	else if (entity->type == powerstation)
	{
		entity->sprite_index = -power_station_ready;
		entity->alt_sprite_index = -power_station_depleted;
	}
	else if (entity->type == lamp)
	{
		entity->sprite_index = -lamp_on;
		entity->alt_sprite_index = -lamp_off;
	}
	else if (entity->type == ammo_pack)
		entity->sprite_index = -ammo_pack_sprite;
	else if (entity->type == keycard_engineering)
		entity->sprite_index = -engineering_keycard_sprite;
	else if (entity->type == keycard_cleaning)
		entity->sprite_index = -cleaning_keycard_sprite;
	else if (entity->type == keycard_military)
		entity->sprite_index = -military_keycard_sprite;
	else
		error_output("ERROR: Static entity texture not found.");
}

static void	initialize_moving_entity_textures(t_entity *entity)
{
	if (entity->type == skull_skulker)
	{
		entity->sprite_index = -enemy0;
		entity->alt_sprite_index = -enemy2;
	}
	else if (entity->type == thing)
	{
		entity->sprite_index = -enemy1;
		entity->alt_sprite_index = -enemy3;
	}
	else
	{
		error_output("ERROR: Moving entity texture not found.");
	}
}

static void	initialize_triangle_index(t_triangle *tri, t_entity *entity)
{
	if (entity->is_static)
	{
		if (entity->is_active && entity->state)
			tri->idx = entity->sprite_index;
		else
			tri->idx = entity->alt_sprite_index;
	}
	else
	{
		if (entity->is_revealed)
			tri->idx = entity->alt_sprite_index;
		else
			tri->idx = entity->sprite_index;
	}
}

Uint32	initialize_entity_textures(t_entity *entity)
{
	if (entity->is_static)
	{
		initialize_static_entity(entity);
		initialize_top_texels(&entity->top);
		initialize_bottom_texels(&entity->bot);
	}
	else
	{
		initialize_moving_entity_textures(entity);
		set_entity_texels_for_frame(entity);
	}
	initialize_triangle_index(&entity->top, entity);
	initialize_triangle_index(&entity->bot, entity);
	return (0);
}