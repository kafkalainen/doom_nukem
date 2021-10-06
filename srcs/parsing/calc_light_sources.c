/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_light_sources.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 13:39:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/06 19:01:36 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	set_new_position(t_sector *sector, t_xyz *light_src, t_xyz isection)
{
	t_xy	centroid;

	centroid = sector->centroid;
	light_src->x = centroid.x;
	light_src->z = centroid.y;
	light_src->y = isection.y;
}

void	calc_light_sources(t_home *home)
{
	t_uint	i;
	t_xyz	isection;
	t_bool	state;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		state = get_ceiling_intersection(home->sectors[i],
				home->sectors[i]->lights.light_src,
				&isection);
		if (state)
		{
			set_new_position(home->sectors[i],
				&home->sectors[i]->lights.light_src,
				isection);
		}
		i++;
	}
}
