/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_light_sources.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 13:39:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/04 19:03:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	set_new_position(t_sector *sector, t_xyz *light_src)
{
	t_xy	centroid;

	centroid = calculate_centroid(sector);
	(*light_src).x = centroid.x;
	(*light_src).z = centroid.y;
}

void	calc_light_sources(t_home *home)
{
	t_uint	i;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		calc_distance_to_ceiling(home->sectors[i],
			&home->sectors[i]->lights.light_src,
			&home->sectors[i]->lights.light_src.y);
		if (home->sectors[i]->lights.light_src.y >= 1.0f)
			home->sectors[i]->lights.light_src.y -= 0.5f;
		set_new_position(home->sectors[i],
			&home->sectors[i]->lights.light_src);
		i++;
	}
}
