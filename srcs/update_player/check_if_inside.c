/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_inside.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:04:32 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/04 10:38:27 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_if_in_current_sector(t_sector *sector, t_xyz *pos)
{
	t_uint			j;
	t_surface		*ground;
	t_xyz			isection;

	j = 0;
	ground = sector->ground;
	while (j < sector->nb_of_ground)
	{
		if (vec3_ray_triangle_intersect(&ground->tri, *pos,
				vec3(0.0f, -1.0f, 0.0f), &isection))
		{
			*pos = isection;
			return (true);
		}
		ground = ground->next;
		j++;
	}
	return (false);
}

int	find_current_sector(t_home *home, t_xyz pos, int cur_idx,
	t_xyz *isection)
{
	t_uint			idx;

	idx = 0;
	if (check_if_in_current_sector(home->sectors[cur_idx], &pos))
	{
		*isection = pos;
		return (cur_idx);
	}
	while (idx < home->nbr_of_sectors)
	{
		if (check_if_in_current_sector(home->sectors[idx], &pos))
		{
			*isection = pos;
			return (idx);
		}
		idx++;
	}
	return (-1);
}
