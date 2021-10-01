/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:13:41 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/01 13:55:46 by jnivala          ###   ########.fr       */
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
	float			g;

	drop_speed = 0.0f;
	g = home->sectors[plr->cur_sector]->gravity;
	if (!check_distance_to_ground(home->sectors[plr->cur_sector],
			plr->height, plr->pos, &drop)
		&& find_current_sector(home, plr->pos) == -1)
		drop = -1.0f;
	if (drop > 0.0f && !plr->input.jetpack)
	{
		plr->drop_time += delta_time;
		drop_speed = g * plr->drop_time * 0.001f;
		if (plr->speed.y < -20.0f)
			plr->dead = 1;
		if (plr->speed.y > 0.0f)
			plr->speed.y -= drop_speed;
		else
			plr->speed.y = -drop_speed;
	}
	else
	{
		if (drop < 0.0f)
			plr->pos.y += ft_fabsf(drop);
		plr->drop_time = 0;
		plr->speed.y = 0.0f;
	}
}

/*
**	t = sqrt(2sg / g)
*/
void	entity_gravity(t_sector *sector, t_home *home, t_entity *entity, Uint32 delta_time)
{
	float			drop;

	drop = -1.0f;
	if (!check_distance_to_ground(sector, entity->legs, entity->pos, &drop))
	{
		entity->falling = 0;
		if (entity->drop_speed >= 5.0f)
			entity->health = 0;
		entity->drop_speed = 0;
		place_entity_to_ground(entity, home);
	}
	if (entity->falling <= 0 && drop > 0.0f)
	{
		entity->falling_total = 0;
		entity->falling = sqrtf(2 * drop / sector->gravity) * 1000;
	}
	else if (entity->falling > 0 && drop != -1.0f)
	{
		entity->falling_total += delta_time;
		entity->falling -= delta_time;
		entity->drop_speed = sector->gravity * entity->falling_total * 0.001f;
		drop = entity->drop_speed * delta_time * 0.001f;
		entity->pos.y -= drop;
	}
}
