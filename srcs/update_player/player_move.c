/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:26 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/13 09:23:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_wall	*check_if_crossing(t_sector *sector, t_xyz pos)
{
	unsigned int	i;
	t_wall			*temp;

	i = 0;
	temp = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (vec3_signed_distance_to_plane(pos, temp->top.normal, temp->top.p[0]))
			return (temp);
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
	t_plane			plane;

	i = 0;
	dir = (t_xyz){0.0f, -1.0f, 0.0f, 0.0f};
	ground = sector->ground;
	while (i < sector->nb_of_ground)
	{
		if (point_inside_a_triangle_surface(ground->tri.p[0],
				ground->tri.p[1], ground->tri.p[2], pos))
			break ;
		ground = ground->next;
		i++;
	}
	plane.point = ground->tri.p[0];
	plane.normal = ground->tri.normal;
	pos = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
	pos.y += plr->height;
	return (pos);
}

static void	viewmodel_motion(t_player *plr)
{
	plr->hud.vm_mx = sin(plr->steps);
	plr->hud.vm_my = sin(plr->steps);
}

Uint32	check_if_allowed_move_through_portal(t_wall *wall, t_player *plr,
				t_home *home, Uint32 t)
{
	if (wall->top.idx >= 0)
	{
		if (check_y_diff(plr, &plr->test_pos, home->sectors[wall->top.idx]))
			return (FALSE);
		if ((wall->is_door && !wall->is_closed && wall->is_locked == unlocked)
			|| !wall->is_door)
		{
			plr->cur_sector = wall->top.idx;
			if (home->sectors[plr->cur_sector]->lights.is_linked == 1)
				home->sectors[plr->cur_sector]->lights.state = TRUE;
			plr->pos = vec3_add(plr->pos, vec3_mul(plr->move_dir, t * 0.005f));
			return (TRUE);
		}
	}
	return (FALSE);
}

int	player_move(t_player *plr, t_home *home, Uint32 t)
{
	t_wall			*wall;
	float			dist;

	plr->move_dir.y = 0.0f;
	plr->move_dir = vec3_unit_vector(plr->move_dir);
	plr->test_pos = vec3_add(plr->pos, vec3_mul(plr->move_dir, t * 0.01f));
	if (check_distance_to_ceiling(home->sectors[plr->cur_sector], &plr->test_pos))
		return (FALSE);
	wall = check_if_crossing(home->sectors[plr->cur_sector], plr->test_pos);
	if (wall)
	{
		if (check_if_allowed_move_through_portal(wall, plr, home, t))
			return (TRUE);
		else
			return (FALSE);
	}
	else
	{
		plr->steps += t * 0.005f;
		plr->pos = vec3_add(plr->pos, vec3_mul(plr->move_dir, t * 0.005f));
		viewmodel_motion(plr);
		dist = check_distance_to_ground(home->sectors[plr->cur_sector], plr->height, plr->pos);
		if (dist < 0 && dist > -plr->height)
			plr->pos.y -= dist;
		return (TRUE);
	}
	return (FALSE);
}
