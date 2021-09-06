/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 13:48:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/06 15:00:01 by jnivala          ###   ########.fr       */
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
	play_sound(plr->audio.thing_attack, 30);
	return (true);
}

static t_bool	skull_skulker_attack(t_entity *entity, t_player *plr, Uint32 t)
{
	if (get_distance_squared(plr->pos, entity->pos) < 2.25f)
	{
		entity->sprite_state = attack;
		if (entity->anim_offset >= 4
			&& (int)(entity->cooldown - t) < 0)
		{
			player_take_damage(plr, 1, t);
			play_sound(plr->audio.skull_skulker_attack, 30);
			return (true);
		}
		pick_next_frame(entity, t);
	}
	return (false);
}

t_bool	attack_player(t_home *home, t_entity *entity, t_player *plr,
		Uint32 t)
{
	if (!entity->is_aggroed)
		return (false);
	if (entity->type == skull_skulker)
		return (skull_skulker_attack(entity, plr, t));
	if (entity->type == thing)
	{
		entity->sprite_state = attack;
		pick_next_frame(entity, t);
		if (entity->anim_offset >= 4
			&& (int)(entity->cooldown - t) < 0)
			shoot_player(home, entity, plr);
		return (true);
	}
	return (false);
}
