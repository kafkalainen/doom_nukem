/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:26 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/11 16:22:18 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_wall	*check_if_crossing(t_sector *sector, t_xyz pos, float cur_height)
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
		{
			if (pos.y + cur_height < temp->top.p[0].y
				|| pos.y + cur_height < temp->top.p[2].y)
				return (temp);
		}
		temp = temp->next;
		i++;
	}
	return (NULL);
}

t_xyz	check_y(t_sector *sector, t_xyz pos, float cur_height)
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
	pos.y += cur_height;
	return (pos);
}

int	player_move(t_player *plr, t_home *home, Uint32 t)
{
	t_wall	*wall;
	t_xyz	new_loc;

	plr->move_dir = vec3_unit_vector(plr->move_dir);
	new_loc = vec3_add(plr->pos, vec3_mul(plr->move_dir, t * 0.05f));
	wall = check_if_crossing(home->sectors[plr->cur_sector], new_loc, plr->height);
	if (wall)
	{
		if (wall->top.idx >= 0)
		{
			if (check_y_diff(&plr->pos, &new_loc, home->sectors[wall->top.idx], plr->height))
				return (FALSE);
			plr->cur_sector = wall->top.idx;
		}
		else
			return (FALSE);
	}
	else
	{
		plr->pos = vec3_add(plr->pos, vec3_mul(plr->move_dir, t * 0.005f));
		plr->pos = check_y(home->sectors[plr->cur_sector], plr->pos, plr->height);
		return (TRUE);
	}
	return (FALSE);
}
