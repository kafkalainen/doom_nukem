/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_distances.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:16:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/16 18:00:06 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	check_distance_to_ceiling(t_sector *sector, t_xyz *new_loc)
{
	unsigned int	i;
	t_surface		*ceiling;
	t_plane			plane;
	float			surf_dist;

	i = 0;
	ceiling = sector->ceiling;
	while (i < sector->nb_of_ground)
	{
		if (point_inside_a_triangle_surface(ceiling->tri.p[0], ceiling->tri.p[1],
				ceiling->tri.p[2], *new_loc))
			break ;
		ceiling = ceiling->next;
		i++;
	}
	plane.point = ceiling->tri.p[0];
	plane.normal = triangle_normal(&ceiling->tri);
	surf_dist = vec3_dot_product(vec3_dec(*new_loc, plane.point),
		plane.normal);
	if (surf_dist <= 0)
		return (TRUE);
	else
		return (FALSE);
}

float	check_distance_to_ground(t_sector *sector, t_player *plr, t_xyz pos)
{
	unsigned int	i;
	t_surface		*ground;
	t_plane			plane;
	float			surf_dist;

	i = 0;
	ground = sector->ground;
	while (i < sector->nb_of_ground)
	{
		if (point_inside_a_triangle_surface(ground->tri.p[0], ground->tri.p[1],
				ground->tri.p[2], pos))
			break ;
		ground = ground->next;
		i++;
	}
	plane.point = ground->tri.p[0];
	plane.normal = triangle_normal(&ground->tri);
	surf_dist = vec3_dot_product(vec3_dec(pos, plane.point),
		plane.normal);
	return (surf_dist - plr->height);
}

// int	check_index_of_a_wall(t_sector *sector, t_xyz pos, t_xyz dir)
// {
// 	unsigned int	i;
// 	t_wall			*wall;
// 	t_plane			plane;
// 	t_triangle		tri;
// 	t_xyz			res;

// 	i = 0;
// 	wall = sector->walls;
// 	while (i < sector->nb_of_walls)
// 	{
// 		if (point_inside_a_triangle_wall(wall->top.p[0], wall->top.p[1],
// 				wall->top.p[2], pos))
// 		{
// 			tri = wall->top;
// 			break ;
// 		}
// 		if (point_inside_a_triangle_wall(wall->bottom.p[0], wall->bottom.p[1],
// 				wall->bottom.p[2], pos))
// 		{
// 			tri = wall->bottom;
// 			break ;
// 		}
// 		wall = wall->next;
// 		i++;
// 	}
// 	return (tri.idx);
// }
