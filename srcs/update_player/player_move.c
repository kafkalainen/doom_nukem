/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:26 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/09 08:13:38 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"
#include <stdio.h>

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
	if (idx != plr->cur_sector && idx != -1)
	{
		ft_putendl("Moving player to current sector.");
		check_if_moved_through_portal(&plr->cur_sector, plr->pos, home);
		printf("idx: %d, cur_sector: %d\n", idx, plr->cur_sector);
		printf("idx nbr_of_walls: %d\n", home->sectors[idx]->nb_of_walls);
		printf("idx nbr_of_ground: %d\n", home->sectors[idx]->nb_of_ground);
		printf("cur_sector nbr_of_walls: %d\n", home->sectors[plr->cur_sector]->nb_of_walls);
		printf("cur_sector nbr_of_ground: %d\n", home->sectors[plr->cur_sector]->nb_of_ground);
		if (idx != plr->cur_sector)
			idx = -1;
	}
	if (idx == -1)
	{
		ft_putendl("Risk of moving out of bounds, move to centroid.");
		printf("x: %f, y: %f, z: %f\n", plr->pos.x, plr->pos.y, plr->pos.z);
		plr->pos = vec3(home->sectors[plr->cur_sector]->centroid.x, 100.0f,
				home->sectors[plr->cur_sector]->centroid.y);
		find_current_sector(home, plr->pos, plr->cur_sector, &isection);
	}
	// ft_putendl("Player in correct sector");
	isection.y += plr->height;
	plr->pos = isection;
}

static void	viewmodel_motion(t_player *plr)
{
	plr->hud.vm_mx = sin(plr->steps);
	plr->hud.vm_my = sin(plr->steps);
}

void	check_if_moved_through_portal(int *cur_sector, t_xyz pos, t_home *home)
{
	Uint32	i;
	t_wall	*portal;

	i = 0;
	portal = home->sectors[*cur_sector]->walls;
	while (i < home->sectors[*cur_sector]->nb_of_walls)
	{
		if (check_if_open_portal(portal))
		{
			if (check_if_in_current_sector(home->sectors[portal->top.type], &pos))
			{
				*cur_sector = portal->top.type;
				automatic_lights(home->sectors[*cur_sector], home);
				return ;
			}
		}
		portal = portal->next;
		i++;
	}
	// printf("not found in next sector, check if moved through portal\n");
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
		check_if_moved_through_portal(&plr->cur_sector, plr->pos, home);
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
