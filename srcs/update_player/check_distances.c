/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_distances.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:16:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/28 11:57:40 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_distance_to_ceiling(t_sector *sector, t_xyz *new_loc)
{
	unsigned int	i;
	t_surface		*ceiling;
	t_xyz			isection;
	t_bool			state;

	i = 0;
	isection = vec3(0, 0, 0);
	ceiling = sector->ceiling;
	while (i < sector->nb_of_ceil)
	{
		state = vec3_ray_triangle_intersect(&ceiling->tri, *new_loc,
				vec3(0.0f, 1.0f, 0.0f), &isection);
		if (state)
			break ;
		ceiling = ceiling->next;
		i++;
	}
	if ((*new_loc).y < (isection.y - 0.35f))
		return (false);
	else
		return (true);
}

t_bool	calc_distance_to_ceiling(t_sector *sector, t_xyz *new_loc,
		float *dist)
{
	unsigned int	i;
	t_surface		*ceiling;
	t_xyz			isection;
	t_bool			state;

	i = 0;
	ceiling = sector->ceiling;
	while (i < sector->nb_of_ceil)
	{
		state = vec3_ray_triangle_intersect(&ceiling->tri, *new_loc,
				vec3(0.0f, 1.0f, 0.0f), &isection);
		if (state)
			break ;
		ceiling = ceiling->next;
		i++;
	}
	if (state)
	{
		*dist = vec3_dot_product(vec3_dec(*new_loc, ceiling->tri.p[0]),
				ceiling->tri.normal);
	}
	return (state);
}

t_bool	calc_distance_to_ground(t_sector *sector, t_xyz *new_loc,
		float *dist)
{
	unsigned int	i;
	t_surface		*ground;
	t_xyz			isection;
	t_bool			state;

	i = 0;
	ground = sector->ground;
	while (i < sector->nb_of_ground)
	{
		state = vec3_ray_triangle_intersect(&ground->tri, *new_loc,
				vec3(0.0f, -1.0f, 0.0f), &isection);
		if (state)
			break ;
		ground = ground->next;
		i++;
	}
	if (state)
	{
		*dist = vec3_dot_product(vec3_dec(*new_loc, ground->tri.p[0]),
				ground->tri.normal);
	}
	return (state);
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

int	find_current_sector(t_home *home, t_xyz pos)
{
	t_uint			idx;
	t_uint			j;
	t_surface		*ground;
	t_xyz			isection;

	idx = 0;
	while (idx < home->nbr_of_sectors)
	{
		j = 0;
		ground = home->sectors[idx]->ground;
		while (j < home->sectors[idx]->nb_of_ground)
		{
			if (vec3_ray_triangle_intersect(&ground->tri, pos,
					vec3(0.0f, -1.0f, 0.0f), &isection))
				return (idx);
			ground = ground->next;
			j++;
		}
		idx++;
	}
	return (-1);
}
