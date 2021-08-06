/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_entity_textures.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 12:21:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/06 13:56:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	initialize_static_entity(t_entity *entity)
{
	if (entity->entity_type == button)
	{
		entity->sprite_index = -button_on;
		entity->alt_sprite_index = -button_off;
	}
	else if (entity->entity_type == powerstation)
	{
		entity->sprite_index = -power_station_ready;
		entity->alt_sprite_index = -power_station_depleted;
	}
	else if (entity->entity_type == lamp)
	{
		entity->sprite_index = -lamp_on;
		entity->alt_sprite_index = -lamp_off;
	}
	else
	{
		error_output("ERROR: Static entity texture not found.");
	}
}

static void	initialize_moving_entity_textures(t_entity *entity)
{
	if (entity->entity_type == skull_skulker)
	{
		entity->sprite_index = -enemy0;
		entity->alt_sprite_index = -enemy2;
	}
	else if (entity->entity_type == thing)
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

/*
**	Initialize top and bottom triangles!!
*/
Uint32	initialize_entity_textures(t_entity *entity)
{
	if (entity->is_static)
		initialize_static_entity(entity);
	else
		initialize_moving_entity_textures(entity);
	initialize_triangle_index(&entity->top, entity);
	initialize_triangle_index(&entity->bot, entity);
	// entity->top.uv[0] = (t_uvz){0.0f, 1.0f, 1.0f};
	// entity->top.uv[1] = (t_uvz){1.0f, 0.0f, 1.0f};
	// entity->top.uv[2] = (t_uvz){0.0f, 0.0f, 1.0f};
	// entity->bot.uv[0] = (t_uvz){0.0f, 1.0f, 1.0f};
	// entity->bot.uv[1] = (t_uvz){1.0f, 1.0f, 1.0f};
	// entity->bot.uv[2] = (t_uvz){1.0f, 0.0f, 1.0f};
	initialize_top_texels(&entity->top);
	initialize_bottom_texels(&entity->bot);
	return (0);
}
