/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_extra_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:05:11 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/11 15:33:53 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static Uint32	check_portal_floor_difference(t_wall *wall1, t_wall *wall2)
{
	if (wall1->bottom.p[0].y != wall2->bottom.p[0].y
		|| wall1->bottom.p[2].y != wall2->bottom.p[2].y)
		return (1);
	else
		return (0);
}

static Uint32	check_portal_ceiling_difference(t_wall *wall1, t_wall *wall2)
{
	if (wall1->top.p[1].y != wall2->top.p[1].y
		|| wall1->top.p[2].y != wall2->top.p[2].y)
		return (1);
	else
		return (0);
}

static void	generate_a_new_lower_wall(t_wall *portal, t_wall *portal_behind)
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
	if (portal->next->top.idx < 0)
		left.idx = portal->next->top.idx;
	else
		left.idx = -2;
	new_wall = new_point(&left, &right);
	if (!new_wall)
		return ;
	add_to_middle(&portal, new_wall);
}

static void	generate_a_new_top_wall(t_wall *portal, t_wall *portal_behind)
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
	if (portal->next->top.idx < 0)
		left.idx = portal->next->top.idx;
	else
		left.idx = -2;
	new_wall = new_point(&left, &right);
	if (!new_wall)
		return ;
	add_to_middle(&portal, new_wall);
}

void	calc_extra_walls(t_home *home, Uint32 idx)
{
	Uint32	i;
	t_wall	*current_portal;
	t_wall	*portal_behind;
	Uint32	ceil_diff;
	Uint32	floor_diff;
	Uint32	new_walls;

	i = 0;
	ceil_diff = 0;
	floor_diff = 0;
	new_walls = 0;
	current_portal = home->sectors[idx]->walls;
	while (i < home->sectors[idx]->nb_of_walls)
	{
		if (current_portal->top.idx >= 0)
		{
			portal_behind = get_portal_by_idx(idx,
								home->sectors[current_portal->top.idx]);
			if (check_portal_floor_difference(current_portal, portal_behind))
				floor_diff = 1;
			if (check_portal_ceiling_difference(current_portal, portal_behind))
				ceil_diff = 1;
			if (floor_diff && !ceil_diff)
			{
				generate_a_new_lower_wall(current_portal, portal_behind);
				new_walls++;
			}
			if (!floor_diff && ceil_diff)
			{
				generate_a_new_top_wall(current_portal, portal_behind);
				new_walls++;
			}
			if (ceil_diff && floor_diff)
			{
				generate_a_new_top_wall(current_portal, portal_behind);
				current_portal = current_portal->next;
				generate_a_new_lower_wall(current_portal, portal_behind);
				home->sectors[idx]->nb_of_walls += 2;
				new_walls += 2;
				current_portal = current_portal->next;
			}
		}
		current_portal = current_portal->next;
		i++;
	}
	home->sectors[idx]->nb_of_walls += new_walls;
}
