/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 13:48:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/02 12:31:39 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_bool	shoot_player(t_home *home, t_entity *entity)
{
	t_ray	ray;

	ray.side = ENEMY;
	ray.pos = entity->pos;
	ray.dir = entity->dir;
	ray.start_sector = entity->sector_idx;
	shooting_handle(home, &ray);
	return (true);
}

t_bool	attack_player(t_home *home, t_entity *entity, t_player *plr,
		Uint32 t)
{
	if (!entity->is_aggroed)
		return (false);
	if (entity->entity_type == skull_skulker)
	{
		if (get_distance_squared(plr->pos, entity->pos) < 2.25f)
		{
			entity->sprite_state = attack;
			if (entity->anim_offset >= 4
				&& (int)(entity->cooldown - t) < 0)
				plr->power_points--;
			pick_next_frame(entity, t);
			return (false);
		}
	}
	if (entity->entity_type == thing)
	{
		entity->sprite_state = attack;
		pick_next_frame(entity, t);
		if (entity->anim_offset >= 4
				&& (int)(entity->cooldown - t) < 0)
			shoot_player(home, entity);
		return (true);
	}
	return (false);
}
