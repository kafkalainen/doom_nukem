/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sector_height.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 08:55:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/28 12:08:35 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_if_vertically_possible(t_home *home, t_xyz test_pos, float height,
		int cur_sector)
{
	float	dist_to_ceiling;
	float	dist_to_ground;

	if (!calc_distance_to_ceiling(home->sectors[cur_sector],
			&test_pos, &dist_to_ceiling))
	{
		cur_sector = find_current_sector(home, test_pos);
		if (cur_sector == -1)
			return (false);
		calc_distance_to_ceiling(home->sectors[cur_sector],
			&test_pos, &dist_to_ceiling);
	}
	if (!calc_distance_to_ground(home->sectors[cur_sector],
			&test_pos, &dist_to_ground))
	{
		cur_sector = find_current_sector(home, test_pos);
		if (cur_sector == -1)
			return (false);
		calc_distance_to_ground(home->sectors[cur_sector],
			&test_pos, &dist_to_ground);
	}
	if (height <= (dist_to_ceiling + dist_to_ground))
		return (true);
	return (false);
}
