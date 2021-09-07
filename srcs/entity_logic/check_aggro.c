/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_aggro.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 13:14:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/07 13:05:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_bool	check_for_close_range(float distance_squared,
	t_player *plr, t_entity *entity)
{
	if (distance_squared <= AGGRO_RANGE_2
		&& plr->cur_sector == entity->sector_idx)
	{
		if (vec3_dot_product(entity->vec_to_plr, entity->dir) > 0.0f)
		{
			entity->is_aggroed = 1;
			return (true);
		}
	}
	return (false);
}

static t_bool	check_if_in_next_sector(t_home *home,
	t_player *plr, t_entity *entity, int sector_idx)
{
	unsigned int	i;
	t_wall			*wall;

	i = 0;
	wall = home->sectors[sector_idx]->walls;
	if (vec3_dot_product(entity->vec_to_plr, entity->dir) > SQR2)
	{
		while (i++ < home->sectors[sector_idx]->nb_of_walls)
		{
			if (check_if_open_portal(wall)
				&& vec3_dot_product(
					vec3_mul(entity->dir, -1.0f), wall->top.normal) > 0.0f)
			{
				if (wall->top.idx == plr->cur_sector)
				{
					entity->is_aggroed = 1;
					return (true);
				}
				else
					check_if_in_next_sector(home, plr, entity, wall->top.idx);
			}
			wall = wall->next;
		}
	}
	return (false);
}

t_bool	check_aggro(t_player *plr, t_entity *entity, t_home *home)
{
	float			distance_squared;

	distance_squared = get_distance_squared(entity->pos, plr->pos);
	if (plr->cur_sector == entity->sector_idx
		&& check_for_close_range(distance_squared, plr, entity))
	{
		if (entity->type == skull_skulker)
			play_sound(plr->audio.skull_skulker_aggro, 20);
		else if (entity->type == thing)
			play_sound(plr->audio.thing_aggro, 20);
		entity->velocity = 0.0025f;
		return (true);
	}
	if (distance_squared <= AGGRO_RANGE_2
		&& plr->cur_sector != entity->sector_idx
		&& check_if_in_next_sector(home, plr, entity, entity->sector_idx))
	{
		if (entity->type == skull_skulker)
			play_sound(plr->audio.skull_skulker_aggro, 20);
		else if (entity->type == thing)
			play_sound(plr->audio.thing_aggro, 20);
		entity->velocity = 0.0025f;
		return (true);
	}
	return (false);
}
