/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_light_sources.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 13:39:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/29 15:07:06 by rzukale          ###   ########.fr       */
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
		if (vec2_eucl_dist(home->sectors[i]->bounding_box.top_left,
				home->sectors[i]->bounding_box.bottom_right) < 1.42f
			|| vec2_eucl_dist(home->sectors[i]->bounding_box.top_left,
				home->sectors[i]->bounding_box.bottom_left) < 1.42f
			|| vec2_eucl_dist(home->sectors[i]->bounding_box.top_right,
				home->sectors[i]->bounding_box.bottom_right) < 1.42f
			|| vec2_eucl_dist(home->sectors[i]->bounding_box.top_right,
				home->sectors[i]->bounding_box.top_left) < 1.42f
			|| vec2_eucl_dist(home->sectors[i]->bounding_box.bottom_left,
				home->sectors[i]->bounding_box.bottom_right) < 1.42f)
			set_new_position(home->sectors[i],
				&home->sectors[i]->lights.light_src);
		i++;
	}
}
