/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_entity_triangles.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:41:54 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/29 10:00:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_xy	size_logic(t_entity *entity)
{
	t_xy	size;

	if (entity->type == powerstation)
		size = vec2(1.0f, 2.0f);
	else if (entity->type == crewmember
		|| entity->type == thing)
		size = vec2(4.0f, 4.0f);
	else if (entity->type == lift_button
		|| entity->type == light_button
		|| (entity->type >= lamp
			&& entity->type <= keycard_military))
		size = vec2(0.5f, 0.5f);
	else if (entity->type == skull_skulker || entity->type == drone)
		size = vec2(1.25f, 1.25f);
	return (size);
}

void	initialize_top_triangle(int type, t_triangle *top, t_xy size)
{
	if (type == lamp || type == -bullet_decal)
	{
		top->p[0] = (t_xyz){-0.5f * size.x, 0.0f, -0.5f * size.y, 1.0f};
		top->p[1] = (t_xyz){-0.5f * size.x, 0.0f, 0.5f * size.y, 1.0f};
		top->p[2] = (t_xyz){0.5f * size.x, 0.0f, 0.5f * size.y, 1.0f};
	}
	else
	{
		top->p[0] = (t_xyz){-0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
		top->p[1] = (t_xyz){-0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
		top->p[2] = (t_xyz){0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
	}
	top->hull = false;
}

void	initialize_bot_triangle(int type, t_triangle *bot, t_xy size)
{
	if (type == lamp || type == -bullet_decal)
	{
		bot->p[0] = (t_xyz){-0.5f * size.x, 0.0f, -0.5f * size.y, 1.0f};
		bot->p[1] = (t_xyz){0.5f * size.x, 0.0f, 0.5f * size.y, 1.0f};
		bot->p[2] = (t_xyz){0.5f * size.x, 0.0f, -0.5f * size.y, 1.0f};
	}
	else
	{
		bot->p[0] = (t_xyz){-0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
		bot->p[1] = (t_xyz){0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
		bot->p[2] = (t_xyz){0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
	}
	bot->hull = false;
}

void	initialize_entity_triangles(t_entity *entity)
{
	t_xy	size;

	size = size_logic(entity);
	initialize_top_triangle(entity->type, &entity->top, size);
	initialize_bot_triangle(entity->type, &entity->bot, size);
	if (entity->type == thing)
	{
		entity->height = 1.5f;
		entity->legs = 1.0f;
	}
	else
	{
		entity->height = size.y;
		entity->legs = size.y * 0.3f;
	}
	entity->width = 0.8f;
}
