/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:13:41 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/07 16:10:05 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**	We calculate the how much player will drop between frames.
**	Gravity function is based on speed, which we get from
**	v = g * t
**
*/

static float	calculate_speed(float g, float t, float speed)
{
	if (speed > 0.0f)
		speed -= g * t;
	else
		speed = -g * t;
	return (speed);
}

void	gravity(t_home *home, t_player *plr, Uint32 delta_time)
{
	float			drop;
	float			g;

	drop = -1.0f;
	g = home->sectors[plr->cur_sector]->gravity;
	if (!check_distance_to_ground(home->sectors[plr->cur_sector],
			plr->height, plr->pos, &drop) || (drop <= 0.07f))
	{
		plr->drop_time = 0;
		if (plr->speed.y < -5.0f)
			player_take_damage(plr, plr->speed.y / -5.0f, delta_time);
		plr->speed.y = 0.0f;
		player_place_feet_to_ground(plr, home);
	}
	if (drop > 0.0f && !plr->input.jetpack)
	{
		plr->drop_time += delta_time;
		plr->speed.y = calculate_speed(g,
				plr->drop_time * 0.001f, plr->speed.y);
	}
	if (plr->input.jetpack)
		plr->drop_time = 0;
}

/*
**	t = sqrt(2sg / g)
*/
void	entity_gravity(t_sector *sector, t_home *home,
		t_entity *entity, Uint32 delta_time)
{
	float			drop;

	drop = -1.0f;
	if (!check_distance_to_ground(sector, entity->legs, entity->pos, &drop)
		|| drop <= 0.0f)
	{
		entity->falling = 0;
		if (entity->drop_speed >= 5.0f)
			entity->health -= entity->drop_speed / 5.0f;
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
