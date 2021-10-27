/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_button_locations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:13:05 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/11 08:39:06 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	get_midpoint_of_wall(t_xy a, t_xy b, t_xyz *pos)
{
	t_xy	mid;

	if (a.x < b.x)
		mid.x = (b.x + a.x) * 0.5;
	else
		mid.x = (a.x + b.x) * 0.5;
	if (a.y < b.y)
		mid.y = (b.y + a.y) * 0.5;
	else
		mid.y = (a.y + b.y) * 0.5;
	mid.w = 0.0f;
	(*pos).x = mid.x;
	(*pos).z = mid.y;
}

static t_bool	compare_int_midpoint_of_wall(t_wall *wall, t_entity *entity)
{
	t_screen_xy		midpoint;

	if (wall->point.x < wall->next->point.x)
		midpoint.x = (wall->next->point.x + wall->point.x) * 0.5;
	else
		midpoint.x = (wall->point.x + wall->next->point.x) * 0.5;
	if (wall->point.y < wall->next->point.y)
		midpoint.y = (wall->next->point.y + wall->point.y) * 0.5;
	else
		midpoint.y = (wall->point.y + wall->next->point.y) * 0.5;
	if (midpoint.x == entity->pos.x && entity->pos.z == midpoint.y)
		return (true);
	return (false);
}

static t_bool	get_approximate_location(t_sector *sector, t_entity *entity)
{
	t_uint	i;
	t_wall	*wall;

	i = 0;
	wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (compare_int_midpoint_of_wall(wall, entity))
		{
			get_midpoint_of_wall(wall->point, wall->next->point, &entity->pos);
			return (true);
		}
		i++;
		wall = wall->next;
	}
	return (false);
}

static t_bool	get_exact_location(t_sector *sector, t_entity *entity)
{
	t_uint		i;
	t_wall		*wall;
	t_screen_xy	int_normal;
	t_xy		normal;

	i = 0;
	wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		normal = vec2_normal(wall->point, wall->next->point);
		int_normal = (t_screen_xy){normal.x, normal.y};
		normal = (t_xy){entity->pos.x, entity->pos.z, 0.0f};
		if ((point_is_on_the_lseg(wall->point, normal, wall->next->point)
				|| (vec2_check_if_same_point(wall->next->point, normal)))
			&& (int_normal.x == entity->dir.x && int_normal.y == entity->dir.z))
		{
			get_midpoint_of_wall(wall->point, wall->next->point, &entity->pos);
			return (true);
		}
		i++;
		wall = wall->next;
	}
	return (false);
}

void	calc_wall_asset_locations(t_home *home)
{
	t_uint		i;

	i = 0;
	while (i < home->nbr_of_entities)
	{
		if (home->entity_pool[i]->type == light_button
			|| home->entity_pool[i]->type == lift_button
			|| home->entity_pool[i]->type == powerstation
			|| home->entity_pool[i]->type == poster)
		{
			if (!get_exact_location(
					home->sectors[home->entity_pool[i]->sector_idx],
					home->entity_pool[i]))
				get_approximate_location(
					home->sectors[home->entity_pool[i]->sector_idx],
					home->entity_pool[i]);
		}
		i++;
	}
}
