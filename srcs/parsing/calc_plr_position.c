/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_plr_position.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:39:30 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/28 17:04:50 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	calc_plr_position(t_sector *sector, t_player *plr)
{
	t_xy	centroid;

	if (vec2_eucl_dist(sector->bounding_box.top_left,
			sector->bounding_box.bottom_right) < 1.42f
		|| vec2_eucl_dist(sector->bounding_box.top_left,
			sector->bounding_box.bottom_left) < 1.42f
		|| vec2_eucl_dist(sector->bounding_box.top_right,
			sector->bounding_box.bottom_right) < 1.42f)
	{
		centroid = calculate_centroid(sector);
		plr->pos.x = centroid.x;
		plr->pos.z = centroid.y;
	}
}
