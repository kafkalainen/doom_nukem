/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:31:48 by rzukale           #+#    #+#             */
/*   Updated: 2021/08/12 14:23:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float	get_distance_squared(t_xyz pt0, t_xyz pt1)
{
	return (((pt1.x - pt0.x) * (pt1.x - pt0.x) +
		(pt1.y - pt0.y) * (pt1.y - pt0.y) +
		(pt1.z - pt0.z) * (pt1.z - pt0.z)));
}

// int	check_aggro(t_player *plr, t_entity *entity, t_sector *sector)
// {
// 	float			distance_squared;
// 	Uint32			signed_dst;
// 	unsigned int	i;
// 	t_wall			*wall;

// 	distance_squared = get_distance_squared(entity->pos, plr->pos);
// 	signed_dst = vec3_signed_distance_to_plane(plr->pos, entity->dir, entity->pos);
// 	if (distance_squared <= AGGRO_RANGE_1 && signed_dst == 0 && plr->cur_sector == entity->sector_idx)
// 	{
// 		entity->is_aggroed = 1;
// 		return (1);
// 	}
// 	if (distance_squared <= AGGRO_RANGE_1 && signed_dst == 0 && plr->cur_sector != entity->sector_idx)
// 	{
// 		wall = sector->walls;
// 		i = 0;
// 		while (i < sector->nb_of_walls)
// 		{
// 			if (check_if_portal(wall))
// 			{
// 				if ((wall->is_door && !wall->is_closed) || !wall->is_door)
// 				{
// 					if (check_intersection(wall, vec3_to_vec2(entity->pos), vec3_to_vec2(plr->pos)))
// 					{
// 						entity->is_aggroed = 1;
// 						return (1);
// 					}
// 				}
// 			}
// 			i++;
// 			wall = wall->next;
// 		}
// 	}
// 	if (distance_squared <= 1)
// 	{
// 		entity->is_aggroed = 1;
// 		return (1);
// 	}
// 	return (0);
// }

void	choose_new_direction(t_entity *entity, t_home *home)
{
	int		dir;
	t_xyz	pos;

	(void)home;
	dir = rand() % 8;
	dir = 0;
	if (dir == 0) // move south
	{
		pos.x = S;
		pos.y = 0;
		pos.z = 0;
		pos.w = 1;
		entity->dir = vec3_unit_vector(vec3_dec(entity->pos, pos));
		// entity->top = rotate_triangle(&entity->top, 180, 'y');
		// entity->bot = rotate_triangle(&entity->bot, 180, 'y');
		// entity->dir = triangle_normal(&entity->top);
	}
	if (dir == 1) // move south-west
		entity->dir.x = SW;
	if (dir == 2) // move west
		entity->dir.x = W;
	if (dir == 3) // move north-west
		entity->dir.x = NW;
	if (dir == 4) // move north
		entity->dir.x = N;
	if (dir == 5) // move north-east
		entity->dir.x = NE;
	if (dir == 6) // move east
		entity->dir.x = E;
	if (dir == 7) // move south-east
		entity->dir.x = SE;
}

t_xyz	entity_check_y(t_sector *sector, int one, t_xyz pos)
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

int	entity_check_y_diff(t_entity *entity, t_xyz *test_pos, t_sector *to)
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

void	entity_chase(t_entity *entity, t_home *home, Uint32 t, t_player *plr)
{
	t_xyz	new_loc;
	t_xyz	test;
	t_xyz	testi;
	t_wall	*wall;

	testi = vec3_dec(plr->pos, entity->pos);
	new_loc = vec3_unit_vector(testi);
	new_loc.y = 0;
	test = vec3_add(entity->pos, vec3_mul(new_loc, t * 0.005f));
	wall = check_if_crossing(home->sectors[entity->sector_idx], test);
	if (wall)
	{
		if (wall->top.idx >= 0)
		{
			if ((wall->is_door && !wall->is_closed) || !wall->is_door)
			{
				entity->sector_idx = wall->top.idx;
			 	entity->pos = vec3_add(entity->pos, vec3_mul(new_loc, t * 0.005f));
				// increment sprite status, if over the range, reset to 0
			}
		}
		else
		{
			//printf("hit a wall, need to rotate\n");
			// choose_new_direction(entity, home, plr_dir);
			// reset sprite status to 0
			entity->top = rotate_triangle(&entity->top, 180, 'y');
			entity->bot = rotate_triangle(&entity->bot, 180, 'y');
			entity->dir = triangle_normal(&entity->top);
			//printf("new direction: x: %f y: %f z: %f\n", entity->dir.x, entity->dir.y, entity->dir.z);
		}
	}
	else
	{
		entity->pos = vec3_add(entity->pos, vec3_mul(new_loc, t * 0.0005f));
		// increment sprite status, if over the range, reset to 0
		// dist = check_distance_to_ground(home->sectors[entity->sector_idx], entity, entity->pos);
		// if (dist < 0 && dist > -plr->height)
		// 	plr->pos.y -= dist;
		// add_motion(&plr->pos, t);
	}
}

int	entity_move(t_entity *entity, t_home *home, Uint32 t)
{
	t_wall			*wall;
	t_xyz			new_loc;

	new_loc = vec3_add(entity->pos, vec3_mul(entity->dir, t * 0.005f));
	wall = check_if_crossing(home->sectors[entity->sector_idx], new_loc);
	if (wall)
	{
		if (wall->top.idx >= 0)
		{
			if (entity_check_y_diff(entity, &new_loc, home->sectors[wall->top.idx]))
				return (FALSE);
			if ((wall->is_door && !wall->is_closed) || !wall->is_door)
			{
				entity->sector_idx = wall->top.idx;
			 	entity->pos = vec3_add(entity->pos, vec3_mul(entity->dir, t * 0.005f));
				// increment sprite status, if over the range, reset to 0
				return (TRUE);
			}
		}
		else
		{
			//printf("hit a wall, need to rotate\n");
			// choose_new_direction(entity, home);
			entity->top = rotate_triangle(&entity->top, 180, 'y');
			entity->bot = rotate_triangle(&entity->bot, 180, 'y');
			entity->top.normal = triangle_normal(&entity->top);
			entity->bot.normal = entity->top.normal;
			entity->dir = entity->top.normal;
			//printf("new direction: x: %f y: %f z: %f\n", entity->dir.x, entity->dir.y, entity->dir.z);
		}
			return (FALSE);
	}
	else
	{
		entity->pos = vec3_add(entity->pos, vec3_mul(entity->dir, t * 0.005f));
		// increment sprite status, if over the range, reset to 0
		// dist = check_distance_to_ground(home->sectors[entity->sector_idx], entity, entity->pos);
		// if (dist < 0 && dist > -plr->height)
		// 	plr->pos.y -= dist;
		// add_motion(&plr->pos, t);
		return (TRUE);
	}
	return (FALSE);
}
