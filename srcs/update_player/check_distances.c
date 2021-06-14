/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_distances.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:16:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/14 16:53:54 by jnivala          ###   ########.fr       */
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
		if (point_inside_a_triangle(ceiling->tri.p[0], ceiling->tri.p[1],
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
		if (point_inside_a_triangle(ground->tri.p[0], ground->tri.p[1],
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
