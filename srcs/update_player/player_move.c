/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:26 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/10 13:50:01 by jnivala          ###   ########.fr       */
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

// static t_xyz	check_floor_height(t_sector *sector, t_xyz pos)
// {
// 	unsigned int	i;
// 	float			t;
// 	t_surface		*ground;
// 	t_plane			plane;
// 	t_xyz			dir;

// 	i = 0;
// 	dir = (t_xyz){0.0f, -1.0f, 0.0f, 0.0f};
// 	ground = sector->ground;
// 	while (i < sector->nb_of_ground)
// 	{
// 		if (point_inside_a_triangle(ground->tri.p[0], ground->tri.p[1],
// 				ground->tri.p[2], pos))
// 			break ;
// 		ground = ground->next;
// 		i++;
// 	}
// 	plane.point = ground->tri.p[0];
// 	plane.normal = triangle_normal(&ground->tri);
// 	pos = vec3_intersection_with_plane(&plane, pos, dir, &t);
// 	pos.y += 2.0f;
// 	return (pos);
// }

int	player_move(t_player *plr, t_home *home)
{
	t_wall *wall;

	wall = check_if_crossing(home->sectors[plr->current_sector], plr->camera);
	if (wall)
	{
		if (wall->top.idx >= 0)
			plr->current_sector = wall->top.idx;
		else
			plr->camera = vec3_dec(plr->camera, vec3_mul(plr->look_dir, 0.05f));
	}
	else
	{
		// plr->camera = check_floor_height(home->sectors[plr->current_sector], plr->camera);
		return (TRUE);
	}
	// if (crossing != NULL && crossing->idx >= 0)
	// {
	// 	if (plr_in_corner(home->sectors[crossing->idx], &pos) !=  open_space)
	// 		return (0);
	// 	if (check_height_diff(dir, &plr->z, crossing,
	// 		get_portal_by_idx(plr->current_sector, home->sectors[crossing->idx])))
	// 		return (0);
	// 	translate_world_view(home, *dir);
	// 	plr->current_sector = crossing->idx;
	// }
	// else if (crossing == NULL)
	// {
	// 	pos = vec2_mul(*dir, 8);
	// 	crossing = check_if_wall(home->sectors[plr->current_sector], dir, &pos);
	// 	if (crossing != NULL && crossing->idx < 0)
	// 		return (0);
	// 	if (plr_in_corner(home->sectors[plr->current_sector], &pos)
	// 		!= open_space)
	// 		return (0);
	// 	if (plr_inside(home->sectors[plr->current_sector], &(t_xy){0.0f, 0.0f}))
	// 	{
	// 		update_height(dir, &plr->z, home->sectors[plr->current_sector]->points,
	// 			home->sectors[plr->current_sector]->nb_of_walls);
	// 		translate_world_view(home, *dir);
	// 	}
	// }
	return (TRUE);
}
