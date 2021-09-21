/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_place_feet_to_ground.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:04:54 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/21 16:29:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	player_place_feet_to_ground(t_home *home, t_player *plr)
{
	float	dist;

	check_distance_to_ground(home->sectors[plr->cur_sector],
		plr->height, plr->pos, &dist);
	if (dist < 0)
		plr->pos.y += ft_fabsf(dist);
}
