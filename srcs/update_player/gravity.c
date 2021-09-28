/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:13:41 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/28 13:00:58 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**	We calculate the how much player will drop between frames.
**	Gravity function is based on speed, which we get from
**	v = g * t
**
*/
void	gravity(t_home *home, t_player *plr, Uint32 delta_time)
{
	float			drop;
	float			drop_speed;
	static Uint32	total_time;

	drop_speed = 0.0f;
	if (!check_distance_to_ground(home->sectors[plr->cur_sector],
			plr->height, plr->pos, &drop)
		&& find_current_sector(home, plr->pos) == -1)
		drop = -1.0f;
	if (drop > 0.0f && !plr->input.jetpack)
	{
		total_time += delta_time;
		drop_speed = 0.5f * total_time * 0.001f;
		if (drop_speed > 1.0f)
			plr->dead = 1;
		plr->speed.y -= drop_speed;
	}
	else
	{
		if (drop < 0.0f)
			plr->pos.y += ft_fabsf(drop);
		total_time = 0;
		plr->speed.y = 0.0f;
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
	check_distance_to_ground(sector, entity->legs, entity->pos, &drop);
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
