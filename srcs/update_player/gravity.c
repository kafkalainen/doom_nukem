/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:13:41 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/14 16:57:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"


//	9.81 m / s 2
// 	1000 * 0.001
void	gravity(t_sector *sector, t_player *plr, Uint32 delta_time)
{
	float			g;
	float			drop;

	g = 9.81f;
	drop = check_distance_to_ground(sector, plr, plr->pos);
	if (drop > 0.0f)
	{
		drop = 0.5f * g * delta_time * delta_time * 0.000001f;
		plr->pos.y -= drop;
	}
	return ;
}
