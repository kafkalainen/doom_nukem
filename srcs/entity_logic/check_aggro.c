/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_aggro.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 13:14:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/05 22:53:10 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_bool	check_for_close_range(Uint32 signed_dst, float distance_squared,
	t_player *plr, t_entity *entity)
{
	if (distance_squared <= AGGRO_RANGE_1
		&& signed_dst == 0
		&& plr->cur_sector == entity->sector_idx)
	{
		entity->is_aggroed = 1;
		return (true);
	}
	return (false);
}

/*
**	REVISIT
*/
static t_bool	check_if_in_next_sector(t_sector *sector,
	float distance_squared, t_player *plr, t_entity *entity)
{
	unsigned int	i;
	t_wall			*wall;
	Uint32			signed_dst;
	t_xyz			vec_to_plr;
	t_xyz			isection;

	i = 0;
	wall = sector->walls;
	signed_dst = vec3_signed_distance_to_plane(plr->pos, entity->dir,
			entity->pos);
	vec_to_plr = vec3_unit_vector(vec3_dec(plr->pos, entity->pos));
	if (distance_squared <= AGGRO_RANGE_2
		&& signed_dst == 0 && plr->cur_sector != entity->sector_idx)
	{
		while (i < sector->nb_of_walls)
		{
			if (check_if_portal(wall)
				&& ((wall->is_door && !wall->is_closed) || !wall->is_door))
			{
				if (vec3_ray_triangle_intersect(&wall->top,
						entity->pos, vec_to_plr, &isection)
					|| vec3_ray_triangle_intersect(&wall->bottom, entity->pos,
						vec_to_plr, &isection))
				{
					if (vec3_dot_product(vec_to_plr, entity->dir) > 0.0f)
					{
						entity->is_aggroed = 1;
						return (true);
					}
				}
			}
			i++;
			wall = wall->next;
		}
	}
	return (false);
}

t_bool	check_aggro(t_player *plr, t_entity *entity, t_sector *sector)
{
	float			distance_squared;
	Uint32			signed_dst;

	distance_squared = get_distance_squared(entity->pos, plr->pos);
	signed_dst = vec3_signed_distance_to_plane(plr->pos, entity->dir,
			entity->pos);
	if (check_for_close_range(signed_dst, distance_squared, plr, entity))
	{
		if (entity->type == skull_skulker)
			play_sound(plr->audio.skull_skulker_aggro, 20);
		else if (entity->type == thing)
			play_sound(plr->audio.thing_aggro, 20);
		return (true);
	}
	if (check_if_in_next_sector(sector, distance_squared, plr,
			entity))
	{
		if (entity->type == skull_skulker)
			play_sound(plr->audio.skull_skulker_aggro, 20);
		else if (entity->type == thing)
			play_sound(plr->audio.thing_aggro, 20);
		return (true);
	}
	return (false);
}
