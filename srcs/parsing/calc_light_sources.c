/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_light_sources.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 13:39:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/28 19:15:40 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	calc_light_sources(t_home *home)
{
	t_uint	i;
	t_xy	centroid;

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
				home->sectors[i]->bounding_box.bottom_right) < 1.42f)
		{
			centroid = calculate_centroid(home->sectors[i]);
			home->sectors[i]->lights.light_src.x = centroid.x;
			home->sectors[i]->lights.light_src.z = centroid.y;
		}
		i++;
	}
}
