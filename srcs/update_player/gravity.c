/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:13:41 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/23 14:32:51 by jnivala          ###   ########.fr       */
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

	g = 1.0f;
	drop = check_distance_to_ground(sector, plr->height, plr->pos);
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
		drop = ft_fmax(drop, 0.0f);
	}
}

/*
**	t = sqrt(2s / g)
*/
void	entity_gravity(t_sector *sector, t_entity *entity, Uint32 delta_time)
{
	float			g;
	float			drop;

	g = 3.0f;
	drop = check_distance_to_ground(sector, entity->legs, entity->pos);
	if (entity->time <= 0 && drop > 0.0f)
		entity->time = sqrtf(2 * drop * 0.5f);
	else if (entity->time > 0 && drop > 0.0f)
	{
		entity->time -= delta_time;
		drop = g * delta_time * 0.0002f;
		entity->pos.y -= drop;
	}
	else
		return ;
}
