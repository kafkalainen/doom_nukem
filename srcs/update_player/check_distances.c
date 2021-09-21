/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_distances.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:16:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/21 16:28:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_distance_to_ceiling(t_sector *sector, t_xyz *new_loc)
{
	unsigned int	i;
	t_surface		*ceiling;
	float			surf_dist;

	i = 0;
	ceiling = sector->ceiling;
	while (i < sector->nb_of_ceil)
	{
		if (point_inside_a_triangle_surface(ceiling->tri.p[0],
				ceiling->tri.p[1], ceiling->tri.p[2], *new_loc))
			break ;
		ceiling = ceiling->next;
		i++;
	}
	surf_dist = vec3_dot_product(vec3_dec(*new_loc, ceiling->tri.p[0]),
			ceiling->tri.normal);
	if (surf_dist <= 0.3f)
		return (true);
	else
		return (false);
}

float	calc_distance_to_ceiling(t_sector *sector, t_xyz *new_loc)
{
	unsigned int	i;
	t_surface		*ceiling;
	float			surf_dist;

	i = 0;
	ceiling = sector->ceiling;
	while (i < sector->nb_of_ceil)
	{
		if (point_inside_a_triangle_surface(ceiling->tri.p[0],
				ceiling->tri.p[1], ceiling->tri.p[2], *new_loc))
			break ;
		ceiling = ceiling->next;
		i++;
	}
	surf_dist = vec3_dot_product(vec3_dec(*new_loc, ceiling->tri.p[0]),
			ceiling->tri.normal);
	return (surf_dist);
}

t_bool	check_distance_to_ground(t_sector *sector, float height,
		t_xyz pos, float *dist)
{
	unsigned int	i;
	t_surface		*ground;
	t_xyz			isection;
	float			surf_dist;
	t_bool			state;

	i = 0;
	ground = sector->ground;
	while (i < sector->nb_of_ground)
	{
		state = vec3_ray_triangle_intersect(&ground->tri, pos,
				vec3(0.0f, -1.0f, 0.0f), &isection);
		if (state)
			break ;
		ground = ground->next;
		i++;
	}
	if (state)
	{
		surf_dist = pos.y - isection.y;
		*dist = surf_dist - height;
		return (true);
	}
	return (false);
}
