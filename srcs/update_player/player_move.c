/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:26 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/30 15:43:11 by jnivala          ###   ########.fr       */
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

void	player_place_feet_to_ground(t_sector *sector, t_player *plr)
{
	unsigned int	i;
	float			dist;
	t_surface		*ground;
	t_xyz			pos;
	t_xyz			isection;

	i = 0;
	dist = 0.0f;
	if (check_distance_to_ground(sector, plr->height, plr->pos, &dist)
		&& dist > 0)
		return ;
	pos = vec3(plr->pos.x, 100.0f, plr->pos.z);
	ground = sector->ground;
	while (i < sector->nb_of_ground)
	{
		if (vec3_ray_triangle_intersect(&ground->tri, pos,
				vec3(0.0f, -1.0f, 0.0f), &isection))
			break ;
		ground = ground->next;
		i++;
	}
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
	float	dist;

	i = 0;
	portal = home->sectors[*cur_sector]->walls;
	while (i < home->sectors[*cur_sector]->nb_of_walls)
	{
		if (check_if_open_portal(portal)
			&& check_distance_to_ground(home->sectors[portal->top.type],
				1.5f, pos, &dist))
		{
			*cur_sector = portal->top.type;
			if (home->sectors[*cur_sector]->lights.is_linked == 1)
				home->sectors[*cur_sector]->lights.state = true;
		}
		portal = portal->next;
		i++;
	}
}

t_bool	player_move(t_player *plr, t_home *home, Uint32 t)
{
	t_wall			*wall;

	plr->move_dir.y = 0.0f;
	plr->move_dir = vec3_unit_vector(plr->move_dir);
	plr->test_pos = vec3_add(plr->pos, vec3_mul(plr->move_dir, t * 0.005f));
	if (!check_if_vertically_possible(home, plr->test_pos, plr->height,
			plr->cur_sector))
		return (false);
	wall = check_if_too_close_to_walls(home->sectors[plr->cur_sector],
			plr->width, plr->test_pos, plr->move_dir);
	if (!wall)
	{
		plr->pos = plr->test_pos;
		check_if_moved_through_portal(&plr->cur_sector, plr->pos, home);
		plr->steps += t * 0.005f;
		viewmodel_motion(plr);
		player_place_feet_to_ground(home->sectors[plr->cur_sector], plr);
		return (true);
	}
	return (strafe_along_the_wall(wall, plr, home, t));
}
