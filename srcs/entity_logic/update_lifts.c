/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_lifts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 14:52:09 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 15:58:57 by jnivala          ###   ########.fr       */
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
		wall->bot = translate_triangle(&wall->bot, direction);
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

void	translate_sector(t_sector *sector, float distance)
{
	t_xyz	translation;

	if (!sector)
		return ;
	translation = (t_xyz){0.0f, distance, 0.0f, 0.0f};
	translate_walls(sector, translation);
	translate_ceiling_and_ground(sector, translation);
	sector->lights.light_src
		= translate_point(&sector->lights.light_src, translation);
}

void	translate_entities(t_home *home, float distance, int sector_idx)
{
	Uint32	i;
	t_xyz	translation;

	i = 0;
	translation = (t_xyz){0.0f, distance, 0.0f, 0.0f};
	while (i < home->nbr_of_entities)
	{
		if (home->entity_pool[i]->sector_idx == sector_idx)
		{
			home->entity_pool[i]->pos
				= vec3_add(home->entity_pool[i]->pos, translation);
		}
		i++;
	}
}

void	update_lifts(t_home *home, t_player *plr, Uint32 delta_time)
{
	Uint32	i;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		if (home->sectors[i]->is_lift == lift)
		{
			if (home->sectors[i]->moving_until > 0)
			{
				translate_sector(home->sectors[i],
					home->sectors[i]->velocity * delta_time * 0.001f);
				translate_entities(home,
					home->sectors[i]->velocity * delta_time * 0.001f, i);
				translate_projectiles(home,
					home->sectors[i]->velocity * delta_time * 0.001f, i);
				plr->pos.y += home->sectors[i]->velocity * delta_time * 0.001f;
				home->sectors[i]->moving_until -= delta_time;
			}
			else
				lock_lift(home, home->sectors[i]);
		}
		i++;
	}
}
