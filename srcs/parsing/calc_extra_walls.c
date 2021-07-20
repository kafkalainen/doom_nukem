/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_extra_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:05:11 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/06 17:23:48 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static Uint32	generate_a_new_lower_wall(t_wall *portal, t_wall *portal_behind)
{
	t_point_data	left;
	t_point_data	right;
	t_wall			*new_wall;

	left.x = portal->bottom.p[0].x;
	right.x = portal->bottom.p[2].x;
	left.y = portal->bottom.p[0].z;
	right.y = portal->bottom.p[2].z;
	left.ceiling = portal_behind->bottom.p[2].y;
	right.ceiling = portal_behind->bottom.p[0].y;
	left.ground = portal->bottom.p[0].y;
	right.ground = portal->bottom.p[2].y;
	portal_behind->bottom.p[2].y = portal->bottom.p[0].y;
	portal_behind->bottom.p[0].y = portal->bottom.p[2].y;
	portal_behind->top.p[0].y = portal->bottom.p[2].y;
	if (portal->next->top.idx < 0)
		left.idx = portal->next->top.idx;
	else
		left.idx = -2;
	new_wall = new_point(&left, &right);
	if (!new_wall)
		return (0);
	add_to_middle(&portal_behind, new_wall);
	return (1);
}

static Uint32	generate_a_new_top_wall(t_wall *portal, t_wall *portal_behind)
{
	t_point_data	left;
	t_point_data	right;
	t_wall			*new_wall;

	left.x = portal->top.p[1].x;
	right.x = portal->top.p[2].x;
	left.y = portal->top.p[1].z;
	right.y = portal->top.p[2].z;
	left.ceiling = portal->top.p[1].y;
	right.ceiling = portal->top.p[2].y;
	left.ground = portal_behind->top.p[2].y;
	right.ground = portal_behind->top.p[1].y;
	portal_behind->top.p[2].y = portal->top.p[1].y;
	portal_behind->top.p[1].y = portal->top.p[2].y;
	portal_behind->bottom.p[1].y = portal->top.p[1].y;
	if (portal->next->top.idx < 0)
		left.idx = portal->next->top.idx;
	else
		left.idx = -2;
	new_wall = new_point(&left, &right);
	if (!new_wall)
		return (0);
	add_to_middle(&portal_behind, new_wall);
	return (1);
}

Uint32	generate_doors(t_wall *current_portal)
{
	t_point_data	left;
	t_point_data	right;
	t_wall			*new_door;

	if (!current_portal->is_door)
		return (0);
	left.x = current_portal->top.p[1].x;
	right.x = current_portal->top.p[2].x;
	left.y = current_portal->top.p[1].z;
	right.y = current_portal->top.p[2].z;
	left.ceiling = current_portal->top.p[1].y;
	right.ceiling = current_portal->top.p[2].y;
	left.ground = current_portal->bottom.p[0].y;
	right.ground = current_portal->bottom.p[2].y;
	left.idx = -door;
	current_portal->is_closed = 1;
	new_door = new_point(&left, &right);
	if (!new_door)
		return (0);
	add_to_middle(&current_portal, new_door);
	return (1);
}

Uint32	generate_wall_logic(t_wall *current_portal, t_wall *portal_behind)
{
	Uint32	ceil_diff;
	Uint32	floor_diff;
	Uint32	walls;

	ceil_diff = 0;
	floor_diff = 0;
	walls = 0;
	if (check_portal_floor_difference(current_portal, portal_behind))
		floor_diff = 1;
	if (check_portal_ceiling_difference(current_portal, portal_behind))
		ceil_diff = 1;
	if (floor_diff && !ceil_diff)
		walls += generate_a_new_lower_wall(current_portal, portal_behind);
	if (!floor_diff && ceil_diff)
		walls += generate_a_new_top_wall(current_portal, portal_behind);
	if (ceil_diff && floor_diff)
	{
		walls += generate_a_new_top_wall(current_portal, portal_behind);
		walls += generate_a_new_lower_wall(current_portal, portal_behind);
	}
	return (walls);
}

void	calc_extra_walls(t_home *home)
{
	Uint32	i;
	Uint32	j;
	t_wall	*current_portal;
	t_wall	*portal_behind;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		j = 0;
		current_portal = home->sectors[i]->walls;
		while (j < home->sectors[i]->nb_of_walls)
		{
			if (current_portal->top.idx >= 0)
			{
				portal_behind = get_portal_by_idx(i,
						home->sectors[current_portal->top.idx]);
				home->sectors[current_portal->top.idx]->nb_of_walls
					+= generate_wall_logic(current_portal, portal_behind);
				home->sectors[i]->nb_of_walls += generate_doors(current_portal);
			}
			current_portal = current_portal->next;
			j++;
		}
		i++;
	}
}
