/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sector_height.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 08:55:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/23 09:08:01 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_sector_height(t_xyz pos, float height, t_sector *sector)
{
	float	dist_to_ceiling;
	float	dist_to_ground;

	if (check_distance_to_ceiling(sector, &pos))
		return (false);
	dist_to_ceiling = calc_distance_to_ceiling(sector, &pos);
	check_distance_to_ground(sector, height, pos, &dist_to_ground);
	if (dist_to_ground + dist_to_ceiling >= height)
		return (true);
	else
		return (false);
}
