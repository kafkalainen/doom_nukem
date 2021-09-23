/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_map_properties.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:13:37 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/23 14:50:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	calc_map_properties(t_home *home, t_player *plr)
{
	unsigned int	i;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		calc_sector_bounds(home->sectors[i]);
		home->sectors[i]->nb_of_ground
			= triangulate_floor(home->sectors[i], 'g');
		home->sectors[i]->nb_of_ceil
			= triangulate_ceiling(home->sectors[i], 'c');
		i++;
	}
	calc_extra_walls(home);
	calc_lift_doors(home);
	calc_unit_normals(home);
	calc_light_sources(home);
	player_place_feet_to_ground(home->sectors[plr->cur_sector], plr);
	assign_entity_properties(home, plr->pos);
	assign_projectiles(home);
}
