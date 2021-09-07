/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_entity_triangles.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:41:54 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/07 13:08:51 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_xy	size_logic(t_entity *entity)
{
	t_xy	size;

	if (entity->type == powerstation)
		size = (t_xy){1.0f, 2.0f};
	else if (entity->type == crewmember
		|| entity->type == thing)
		size = (t_xy){4.0f, 4.0f};
	else if (entity->type == lift_button
		|| entity->type == light_button
		|| (entity->type >= lamp
			&& entity->type <= keycard_military))
		size = (t_xy){0.5f, 0.5f};
	else
		size = (t_xy){2.0f, 2.0f};
	return (size);
}

void	initialize_entity_triangles(t_entity *entity)
{
	t_xy	size;

	size = size_logic(entity);
	entity->top.p[0] = (t_xyz){-0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
	entity->top.p[1] = (t_xyz){-0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
	entity->top.p[2] = (t_xyz){0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
	entity->bot.p[0] = (t_xyz){-0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
	entity->bot.p[1] = (t_xyz){0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
	entity->bot.p[2] = (t_xyz){0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
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
	entity->width = 1.0f;
}
