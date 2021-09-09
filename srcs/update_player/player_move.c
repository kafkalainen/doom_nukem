/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:26 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/09 11:37:28 by jnivala          ###   ########.fr       */
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
			|| vec3_ray_triangle_intersect(&temp->bottom, pos, dir, &isection))
		{
			if (get_distance_squared(pos, isection) <= OPEN_DOOR_DISTANCE)
				return (temp);
		}
		temp = temp->next;
		i++;
	}
	return (NULL);
}

t_xyz	check_y(t_sector *sector, t_player *plr, t_xyz pos)
{
	unsigned int	i;
	t_surface		*ground;
	t_xyz			dir;
	t_xyz			isection;

	i = 0;
	dir = (t_xyz){0.0f, -1.0f, 0.0f, 0.0f};
	ground = sector->ground;
	while (i < sector->nb_of_ground)
	{
		if (vec3_ray_triangle_intersect(&ground->tri, pos, dir, &isection))
			break ;
		ground = ground->next;
		i++;
	}
	isection.y += plr->height;
	return (isection);
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
			if (vec3_signed_distance_to_plane(pos,
					portal->top.normal, portal->top.p[0]) < 0)
			{
				*cur_sector = portal->top.type;
				if (home->sectors[*cur_sector]->lights.is_linked == 1)
					home->sectors[*cur_sector]->lights.state = TRUE;
			}
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
	if (check_distance_to_ceiling(home->sectors[plr->cur_sector],
			&plr->test_pos))
		return (false);
	wall = check_if_too_close_to_walls(home->sectors[plr->cur_sector],
			plr->width, plr->test_pos, plr->move_dir);
	if (!wall)
	{
		plr->pos = plr->test_pos;
		check_if_moved_through_portal(&plr->cur_sector, plr->pos, home);
		plr->steps += t * 0.005f;
		viewmodel_motion(plr);
		player_place_feet_to_ground(home, plr);
		return (true);
	}
	return (strafe_along_the_wall(wall, plr, home, t));
}
