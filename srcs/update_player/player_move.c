/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:26 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/15 09:52:32 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_wall	*check_if_crossing(t_sector *sector, t_xyz pos)
{
	unsigned int	i;
	t_wall			*temp;
	t_plane			plane;

	i = 0;
	temp = sector->walls;
	while (i < sector->nb_of_walls)
	{
		plane.point = temp->top.p[0];
		plane.normal = triangle_normal(&temp->top);
		if (vec3_signed_distance_to_plane(pos, plane.normal, plane.point))
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
		if (point_inside_a_triangle(ground->tri.p[0], ground->tri.p[1],
				ground->tri.p[2], pos))
			break ;
		ground = ground->next;
		i++;
	}
	plane.point = ground->tri.p[0];
	plane.normal = triangle_normal(&ground->tri);
	pos = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
	pos.y += plr->height;
	return (pos);
}

int	player_move(t_player *plr, t_home *home, Uint32 t)
{
	t_wall	*wall;
	t_xyz	new_loc;
	float	dist;

	plr->move_dir.y = 0.0f;
	plr->move_dir = vec3_unit_vector(plr->move_dir);
	new_loc = vec3_add(plr->pos, vec3_mul(plr->move_dir, t * 0.03f));
	if (check_distance_to_ceiling(home->sectors[plr->cur_sector], &new_loc))
		return (FALSE);
	wall = check_if_crossing(home->sectors[plr->cur_sector], new_loc);
	if (wall)
	{
		if (wall->top.idx >= 0)
		{
			if (check_y_diff(plr, &new_loc, home->sectors[wall->top.idx]))
				return (FALSE);
			plr->cur_sector = wall->top.idx;
		}
		else
			return (FALSE);
	}
	else
	{
		plr->pos = vec3_add(plr->pos, vec3_mul(plr->move_dir, t * 0.005f));
		dist = check_distance_to_ground(home->sectors[plr->cur_sector], plr, plr->pos);
		if (dist < 0)
			plr->pos.y -= dist;
		return (TRUE);
	}
	return (FALSE);
}
