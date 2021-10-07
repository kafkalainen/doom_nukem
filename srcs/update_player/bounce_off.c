/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounce_off.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 09:54:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/07 20:45:11 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	bounce_off_the_wall(t_wall *wall, t_player *plr,
		t_home *home, Uint32 t)
{
	t_wall		*new_wall;
	t_entity	*new_entity;

	plr->test_pos = vec3_add(plr->pos, vec3_mul(wall->top.normal, t * 0.0005f));
	new_wall = check_if_too_close_to_walls(home->sectors[plr->cur_sector],
			plr->width, plr->test_pos, wall->top.normal);
	new_entity = walking_into_entity(plr->test_pos, plr,
			home->entity_pool, home->nbr_of_entities);
	if (!new_wall && !new_entity)
	{
		plr->pos = plr->test_pos;
		check_if_moved_through_portal(&plr->cur_sector, plr->pos,
			plr->height, home);
		plr->steps += t * 0.005f;
		return (true);
	}
	else
		return (false);
}

t_bool	bounce_off_entity(t_entity *entity, t_player *plr,
		t_home *home, Uint32 t)
{
	t_wall		*new_wall;
	t_entity	*new_entity;

	plr->test_pos = vec3_add(plr->pos, vec3_mul(entity->top.normal,
				t * 0.0005f));
	new_wall = check_if_too_close_to_walls(home->sectors[plr->cur_sector],
			plr->width, plr->test_pos, entity->top.normal);
	new_entity = walking_into_entity(plr->test_pos, plr,
			home->entity_pool, home->nbr_of_entities);
	if (!new_wall && !new_entity)
	{
		plr->pos = plr->test_pos;
		check_if_moved_through_portal(&plr->cur_sector, plr->pos,
			plr->height, home);
		plr->steps += t * 0.005f;
		return (true);
	}
	else
		return (false);
}

t_bool	entity_bounce_off_the_wall(t_wall *wall, t_entity *entity,
		t_home *home, Uint32 t)
{
	t_wall	*new_wall;

	entity->test_pos = vec3_add(entity->pos, vec3_mul(wall->top.normal,
				entity->velocity * t));
	new_wall = check_if_too_close_to_walls(home->sectors[entity->sector_idx],
			entity->width, entity->test_pos, wall->top.normal);
	if (!new_wall)
	{
		entity->pos = entity->test_pos;
		check_if_moved_through_portal(&entity->sector_idx, entity->pos,
			entity->height, home);
		entity->dir = wall->top.normal;
		return (true);
	}
	else
	{
		if (!vec2_check_if_same_point(wall->point, new_wall->point))
			return (entity_bounce_off_the_wall(new_wall, entity, home, t));
	}
	return (false);
}

t_bool	entity_bounce_off_player(t_entity *entity, t_home *home, Uint32 t)
{
	t_wall	*new_wall;
	t_xyz	vector;

	vector = vec3_unit_vector(vec3(entity->vec_to_plr.x,
				0.0f, entity->vec_to_plr.z));
	entity->test_pos = vec3_add(entity->pos,
			vec3_mul(vector, -entity->velocity * t));
	new_wall = check_if_too_close_to_walls(home->sectors[entity->sector_idx],
			entity->width, entity->test_pos, entity->dir);
	if (!new_wall)
	{
		entity->pos = entity->test_pos;
		check_if_moved_through_portal(&entity->sector_idx, entity->pos,
			entity->height, home);
		return (true);
	}
	else
	{
		if (!vec2_check_if_same_point(new_wall->point, new_wall->point))
			return (entity_bounce_off_the_wall(new_wall, entity, home, t));
	}
	return (false);
}

void	unstuck(t_player *plr, t_home *home)
{
	t_wall			*wall;

	wall = check_if_too_close_to_walls(home->sectors[plr->cur_sector],
			plr->width, plr->pos, plr->move_dir);
	if (wall)
	{
		plr->pos = vec3_add(plr->pos, vec3_mul(wall->top.normal, 0.06f));
		check_if_moved_through_portal(&plr->cur_sector, plr->pos,
			plr->height, home);
	}
}
