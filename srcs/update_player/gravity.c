/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:13:41 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/02 18:30:15 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"


/*
**	We calculate the how much player will drop between frames.
**	Gravity function is based on space.
**	s = 1 / 2 * g * t ** 2
**
*/
void	gravity(t_sector *sector, t_player *plr, Uint32 delta_time)
{
	float			g;
	float			drop;
	static Uint32	total_time;

	g = 1.00f;
	drop = check_distance_to_ground(sector, plr, plr->pos);
	if (drop > 0.0f && !plr->input.jetpack)
	{
		if (plr->input.jetpack)
			total_time = delta_time;
		else
			total_time += delta_time;
		drop = g * delta_time * 0.0002f;
		plr->speed.y -= drop;
	}
	else
	{
		total_time = 0;
		plr->speed.y = 0.0f;
		drop = fmax(drop, 0.0f);
	}
}
