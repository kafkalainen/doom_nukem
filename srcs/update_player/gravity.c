/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:13:41 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/01 12:30:18 by jnivala          ###   ########.fr       */
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
	float			gravity;

	drop_speed = 0.0f;
	gravity = home->sectors[plr->cur_sector]->gravity;
	if (!check_distance_to_ground(home->sectors[plr->cur_sector],
			plr->height, plr->pos, &drop)
		&& find_current_sector(home, plr->pos) == -1)
		drop = -1.0f;
	if (drop > 0.0f && !plr->input.jetpack)
	{
		total_time += delta_time;
		drop_speed = gravity * total_time * 0.001f;
		if (drop_speed > 10.0f)
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
**	t = sqrt(2sg / g)
*/
void	entity_gravity(t_home *home, t_entity *entity, Uint32 delta_time)
{
	float			drop;
	float			drop_speed;

	drop = 0.0f;
	drop_speed = 0.0f;
	check_distance_to_ground(home->sectors[entity->sector_idx],
		entity->legs, entity->pos, &drop);
	if (entity->falling <= 0 && drop > 0.0f)
	{
		entity->falling_total = 0;
		entity->falling = sqrtf(2 * drop * 2.0f) / 2.0f * 1000;
	}
	else if (entity->falling > 0)
	{
		entity->falling_total += delta_time;
		entity->falling -= delta_time;
		printf("%d\n", entity->sector_idx);
		drop_speed = home->sectors[entity->sector_idx]->gravity * entity->falling_total * 0.001f;
		drop = drop_speed * delta_time * 0.001f;
		entity->pos.y -= drop;
		if (entity->falling <= 0)
		{
			place_entity_to_ground(entity, home);
			if (drop_speed >= 5.0f)
				entity->health = 0;
		}
	}
}
