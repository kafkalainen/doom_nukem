/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 13:48:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 18:00:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_bool	shoot_player(t_home *home, t_entity *entity, t_player *plr)
{
	t_ray	ray;

	ray.side = ENEMY;
	ray.pos = entity->pos;
	ray.dir = entity->dir;
	ray.start_sector = entity->sector_idx;
	shooting_handle(home, &ray);
	if (!entity->is_revealed)
		play_sound(plr->audio.thing_attack, 15);
	return (true);
}

static t_bool	skull_skulker_attack(t_entity *entity, t_home *home,
		t_player *plr, Uint32 t)
{
	float	dist;
	t_xyz	plr_feet;

	plr_feet = vec3(plr->pos.x, plr->pos.y - plr->height, plr->pos.z);
	dist = get_distance_squared(plr_feet, entity->pos);
	if (dist < MAX_RANGE && dist >= MIN_RANGE)
	{
		entity->sprite_state = attack;
		pick_next_frame(entity, t, ATTACK_COOLDOWN);
		if (entity->anim_offset >= 4
			&& (int)(entity->cooldown - t) < 0)
		{
			player_take_damage(plr, 1, t);
			if (!entity->is_revealed)
				play_sound(plr->audio.skull_skulker_attack, 15);
			else
				play_sound(plr->audio.rahikainen_hits, 15);
		}
		return (true);
	}
	else if (dist < MIN_RANGE && dist >= STOMP_RANGE)
		entity_bounce_off_player(entity, home, t);
	else if (dist < STOMP_RANGE)
		entity->health = 0;
	return (false);
}

t_bool	attack_player(t_home *home, t_entity *entity, t_player *plr,
		Uint32 t)
{
	if (!entity->is_aggroed)
		return (false);
	if (entity->type == skull_skulker)
		return (skull_skulker_attack(entity, home, plr, t));
	if (entity->type == thing)
	{
		entity->sprite_state = attack;
		pick_next_frame(entity, t, MOVE_COOLDOWN);
		if (entity->anim_offset >= 4
			&& (int)(entity->cooldown - t) <= 0)
			shoot_player(home, entity, plr);
		return (true);
	}
	return (false);
}
