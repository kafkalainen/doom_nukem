/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:26 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 19:45:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_wall	*check_if_crossing(t_sector *sector, t_xyz pos, t_xyz dir)
{
	unsigned int	i;
	t_wall			*temp;
	t_xyz			isection;

	i = 0;
	temp = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (vec3_ray_triangle_intersect(&temp->top, pos, dir, &isection)
			|| vec3_ray_triangle_intersect(&temp->bot, pos, dir, &isection))
		{
			if (get_distance_squared(pos, isection) <= OPEN_DOOR_DISTANCE)
				return (temp);
		}
		temp = temp->next;
		i++;
	}
	return (NULL);
}

void	player_place_feet_to_ground(t_player *plr, t_home *home)
{
	t_xyz			pos;
	t_xyz			isection;
	int				idx;

	isection = vec3(0.0f, 0.0f, 0.0f);
	pos = vec3(plr->pos.x, 100.0f, plr->pos.z);
	idx = find_current_sector(home, pos, plr->cur_sector, &isection);
	if (idx != plr->cur_sector)
		check_if_moved_through_portal(&plr->cur_sector,
			plr->pos, plr->height, home);
	if (idx == -1)
	{
		ft_putendl("Risk of moving out of bounds, move to centroid.");
		plr->pos = vec3(home->sectors[plr->cur_sector]->centroid.x, 100.0f,
				home->sectors[plr->cur_sector]->centroid.y);
		find_current_sector(home, plr->pos, plr->cur_sector, &isection);
	}
	isection.y += plr->height;
	plr->pos = isection;
}

static void	viewmodel_motion(t_player *plr)
{
	plr->hud.vm_mx = sin(plr->steps);
	plr->hud.vm_my = sin(plr->steps);
}

void	check_if_moved_through_portal(int *cur_sector, t_xyz pos, float height,
		t_home *home)
{
	Uint32	i;
	t_wall	*portal;
	float	dist;

	i = 0;
	portal = home->sectors[*cur_sector]->walls;
	while (i < home->sectors[*cur_sector]->nb_of_walls)
	{
		if (check_if_open_portal(portal)
			&& (check_distance_to_ground(home->sectors[portal->top.type],
					height, pos, &dist)
				|| point_is_on_the_lseg(portal->point,
					vec2(pos.x, pos.z), portal->next->point)))
		{
			ft_putendl("UPDATED SECTOR");
			*cur_sector = portal->top.type;
			automatic_lights(home->sectors[*cur_sector], home);
			return ;
		}
		portal = portal->next;
		i++;
	}
}

t_bool	player_move(t_player *plr, t_home *home, Uint32 t)
{
	t_wall			*wall;
	t_entity		*entity;

	plr->move_dir = vec3_normalize_move_dir(plr->move_dir);
	plr->test_pos = vec3_add(plr->pos, vec3_mul(plr->move_dir, t * 0.005f));
	if (!check_if_vertically_possible(home, plr, plr->test_pos))
		return (false);
	wall = check_if_too_close_to_walls(home->sectors[plr->cur_sector],
			plr->width, plr->test_pos, plr->move_dir);
	entity = walking_into_entity(plr->test_pos, plr, home->entity_pool,
			home->nbr_of_entities);
	if (!wall && !entity)
	{
		plr->pos = plr->test_pos;
		check_if_moved_through_portal(&plr->cur_sector,
			plr->pos, plr->height, home);
		plr->steps += t * 0.005f;
		viewmodel_motion(plr);
		return (true);
	}
	if (wall && !entity)
		return (bounce_off_the_wall(wall, plr, home, t));
	if (!wall && entity)
		return (bounce_off_entity(entity, plr, home, t));
	return (false);
}
