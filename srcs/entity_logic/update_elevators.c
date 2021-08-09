/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_elevators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 14:52:09 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/09 13:51:57 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	translate_walls(t_sector *sector, t_xyz direction)
{
	Uint32	i;
	t_wall	*wall;

	i = 0;
	wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		wall->top = translate_triangle(&wall->top, direction);
		wall->bottom = translate_triangle(&wall->bottom, direction);
		wall = wall->next;
		i++;
	}
}

static void	translate_ceiling_and_ground(t_sector *sector,
			t_xyz direction)
{
	Uint32		i;
	t_surface	*ceil_ground;

	i = 0;
	ceil_ground = sector->ground;
	while (i < sector->nb_of_ground)
	{
		ceil_ground->tri = translate_triangle(&ceil_ground->tri, direction);
		ceil_ground = ceil_ground->next;
		i++;
	}
	i = 0;
	ceil_ground = sector->ceiling;
	while (i < sector->nb_of_ceil)
	{
		ceil_ground->tri = translate_triangle(&ceil_ground->tri, direction);
		ceil_ground = ceil_ground->next;
		i++;
	}
}

static Uint32	translate_sector(t_sector *sector, char dir, float distance)
{
	t_xyz	direction;

	if (dir == '+')
		direction = (t_xyz){0.0f, distance, 0.0f, 0.0f};
	else
		direction = (t_xyz){0.0f, -distance, 0.0f, 0.0f};
	translate_walls(sector, direction);
	translate_ceiling_and_ground(sector, direction);
	return (0);
}

static void	translate_entities(t_home *home, char dir,
				float distance, int sector_idx)
{
	Uint32	i;
	t_xyz	direction;

	i = 0;
	if (dir == '+')
		direction = (t_xyz){0.0f, distance, 0.0f, 0.0f};
	else
		direction = (t_xyz){0.0f, -distance, 0.0f, 0.0f};
	while (i < home->nbr_of_entities)
	{
		if (home->entity_pool[i]->sector_idx == sector_idx)
		{
			home->entity_pool[i]->pos =
				vec3_add(home->entity_pool[i]->pos, direction);
		}
		i++;
	}

}

Uint32	update_elevators(t_home *home, t_player *plr,
			Uint32 current_time, Uint32 delta_time)
{
	Uint32	i;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		if (home->sectors[i]->is_elevator &&
			home->sectors[i]->moving_until > current_time)
		{
			if (home->sectors[i]->elevator_dir == '+')
			{
				translate_sector(home->sectors[i], '+', 5.0f * delta_time * 0.001f);
				translate_entities(home, '+', 5.0f * delta_time * 0.001f, i);
			}
			else
			{
				translate_sector(home->sectors[i], '-', 5.0f * delta_time * 0.001f);
				translate_entities(home, '-', 5.0f * delta_time * 0.001f, i);
			}
			plr->pos = check_y(home->sectors[i], plr, plr->pos);
		}
		i++;
	}
	return (1);
}
