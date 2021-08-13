/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:19:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/13 10:53:27 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_xyz	entity_check_y(t_sector *sector, int one, t_xyz pos)
{
	unsigned int	i;
	t_surface		*ground;
	t_xyz			dir;
	t_plane			plane;

	i = 0;
	dir = (t_xyz){0.0f, -1.0f, 0.0f, 0.0f};
	ground = sector->ground;
	while (i < sector->nb_of_ground)
	{
		if (point_inside_a_triangle_surface(ground->tri.p[0],
				ground->tri.p[1], ground->tri.p[2], pos))
			break ;
		ground = ground->next;
		i++;
	}
	plane.point = ground->tri.p[0];
	plane.normal = ground->tri.normal;
	pos = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
	pos.y += one;
	return (pos);
}

static int	entity_check_y_diff(t_entity *entity, t_xyz *test_pos, t_sector *to)
{
	test_pos->y += 1;
	if (check_distance_to_ceiling(to, test_pos))
		return (1);
	test_pos->y -= 1;
	*test_pos = entity_check_y(to, 1, *test_pos);
	if (test_pos->y - entity->pos.y < 3)
		return (0);
	else
		return (1);
}

static void	pick_next_frame(t_entity *entity, Uint32 t)
{
	entity->cooldown = entity->cooldown - t;
	if (entity->cooldown < 0)
	{
		entity->anim_offset++;
		entity->cooldown = ENTITY_COOLDOWN_3;
	}
	if (entity->anim_offset > 4)
		entity->anim_offset = 0;
}

static Uint32	check_if_moving_through_portal(t_wall *wall, t_entity *entity, t_home *home,
				Uint32 t)
{
	t_xyz	new_loc;

	new_loc = vec3_add(entity->pos, vec3_mul(entity->dir, t * 0.01f));
	if (wall->top.idx >= 0)
	{
		if (entity_check_y_diff(entity, &new_loc, home->sectors[wall->top.idx]))
			return (FALSE);
		if ((wall->is_door && !wall->is_closed && wall->is_locked == unlocked)
			|| !wall->is_door)
		{
			entity->sector_idx = wall->top.idx;
			entity->pos = vec3_add(entity->pos, vec3_mul(entity->dir, t * 0.0005f));
			pick_next_frame(entity, t);
			return (TRUE);
		}
	}
	return (FALSE);
}


int		entity_move(t_entity *entity, t_home *home, Uint32 t)
{
	t_wall			*wall;
	t_xyz			new_loc;
	float			dist;

	entity->dir.y = 0.0f;
	entity->dir = vec3_unit_vector(entity->dir);
	new_loc = vec3_add(entity->pos, vec3_mul(entity->dir, t * 0.01f));
	wall = check_if_crossing(home->sectors[entity->sector_idx], new_loc);
	if (wall)
	{
		if (check_if_moving_through_portal(wall, entity, home, t))
			return (TRUE);
		else
		{
			entity->dir = wall->top.normal;
			return (FALSE);
		}
	}
	else
	{
		entity->pos = vec3_add(entity->pos, vec3_mul(entity->dir, t * 0.0005f));
		pick_next_frame(entity, t);
		dist = check_distance_to_ground(home->sectors[entity->sector_idx],
			entity->legs, entity->pos);
		if (dist != entity->legs)
			entity->pos.y = dist + entity->legs;
		return (TRUE);
	}
	return (FALSE);
}
