/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:19:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/09 08:01:48 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	pick_next_frame(t_entity *entity, Uint32 t, int cooldown)
{
	entity->cooldown = (int)(entity->cooldown - (int)t);
	if (entity->cooldown <= 0)
	{
		entity->anim_offset++;
		entity->cooldown = cooldown;
	}
	if (entity->anim_offset > ENTITY_SPRITE_MOVE_END)
		entity->anim_offset = ENTITY_SPRITE_MOVE_START;
}

void	place_entity_to_ground(t_entity *entity, t_home *home)
{
	t_xyz			pos;
	t_xyz			isection;
	int				idx;

	isection = vec3(0.0f, 0.0f, 0.0f);
	pos = vec3(entity->pos.x, 100.0f, entity->pos.z);
	idx = find_current_sector(home, pos, entity->sector_idx, &isection);
	if (idx == -1)
		return ;
	entity->sector_idx = idx;
	isection.y += entity->legs;
	entity->pos = isection;
}

t_bool	entity_move(t_entity *entity, t_xyz plr_pos, t_home *home, Uint32 t)
{
	t_wall			*wall;

	entity->dir.y = 0.0f;
	entity->dir = vec3_unit_vector(entity->dir);
	entity->test_pos = vec3_add(entity->pos,
			vec3_mul(entity->dir, t * entity->velocity));
	if (!entity->is_aggroed && get_distance_squared(entity->pos, plr_pos)
		< MIN_RANGE)
		return (false);
	if (check_distance_to_ceiling(home->sectors[entity->sector_idx],
			&entity->test_pos))
		return (false);
	wall = check_if_too_close_to_walls(home->sectors[entity->sector_idx],
			entity->width, entity->test_pos, entity->dir);
	if (!wall)
	{
		entity->pos = entity->test_pos;
		pick_next_frame(entity, t, MOVE_COOLDOWN);
		check_if_moved_through_portal(&entity->sector_idx, entity->pos, home);
		return (true);
	}
	return (entity_bounce_off_the_wall(wall, entity, home, t));
}
