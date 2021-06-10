/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:26 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/10 16:01:47 by jnivala          ###   ########.fr       */
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

static t_xyz	check_floor_height(t_sector *sector, t_xyz pos)
{
	unsigned int	i;
	t_surface		*ground;
	t_plane			plane;
	t_xyz			dir;

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
	pos.y += 1.5f;
	return (pos);
}

int	player_move(t_player *plr, t_home *home, Uint32 delta_time)
{
	t_wall	*wall;
	t_xyz	test_pos;

	plr->move_dir = vec3_unit_vector(plr->move_dir);
	test_pos = vec3_add(plr->camera, vec3_mul(plr->move_dir, delta_time * 0.05f));
	wall = check_if_crossing(home->sectors[plr->current_sector], test_pos);
	if (wall)
	{
		if (wall->top.idx >= 0)
			plr->current_sector = wall->top.idx;
		else
			return (FALSE);
	}
	else
	{
		plr->camera = vec3_add(plr->camera, vec3_mul(plr->move_dir, delta_time * 0.005f));
		plr->camera = check_floor_height(home->sectors[plr->current_sector], plr->camera);
		return (TRUE);
	}
	return (FALSE);
}
