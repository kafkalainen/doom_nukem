/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_extra_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:05:11 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/11 13:13:50 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// static Uint32	check_portal_floor_difference(t_wall *wall1, t_wall *wall2)
// {
// 	if (wall1->bottom.p[0].y != wall2->bottom.p[0].y
// 		|| wall1->bottom.p[2].y != wall2->bottom.p[2].y)
// 		return (1);
// 	else
// 		return (0);
// }

// static Uint32	check_portal_ceiling_difference(t_wall *wall1, t_wall *wall2)
// {
// 	if (wall1->top.p[1].y != wall2->top.p[1].y
// 		|| wall1->top.p[2].y != wall2->top.p[2].y)
// 		return (1);
// 	else
// 		return (0);
// }

// static void	generate_a_new_wall(t_wall *portal, t_wall *portal_behind, char choice)
// {
// 	t_point_data	left;
// 	t_point_data	right;

// 	if (choice == 'c')
// 	{
// 		left.x = portal->top.p[1].x;
// 		right.x = portal->top.p[2].x;
// 		left.y = portal->top.p[1].z;
// 		right.y = portal->top.p[2].z;
// 		left.ceiling = portal->top.p[1].y;
// 		right.ceiling = portal->top.p[2].y;
// 		left.ground = portal_behind->top.p[1].y;
// 		right.ground = portal_behind->top.p[2].y;
// 		new_point(&left, &right);
// 	}
// 	else
// 	{
// 		left.x = portal->top.p[0].x;
// 		right.x = portal->top.p[2].x;
// 		left.y = portal->top.p[0].z;
// 		right.y = portal->top.p[2].z;
// 		left.ceiling = portal->top.p[0].y;
// 		right.ceiling = portal->top.p[2].y;
// 		left.ground = portal_behind->top.p[0].y;
// 		right.ground = portal_behind->top.p[2].y;
// 		new_point(&left, &right);
// 	}
// }

void	calc_extra_walls(t_home *home, Uint32 idx)
{
	Uint32	i;
	t_wall	*current_portal;
	// t_wall	*portal_behind;
	// Uint32	ceil_diff;
	// Uint32	floor_diff;

	i = 0;
	// ceil_diff = 0;
	// ceil_diff = 0;
	current_portal = home->sectors[idx]->walls;
	while (i < home->sectors[idx]->nb_of_walls)
	{
		if (current_portal->top.idx >= 0)
		{
			// portal_behind = get_portal_by_idx(i,
			// 					home->sectors[current_portal->top.idx]);
				return ;
			// if (check_portal_floor_difference(current_portal, portal_behind))
			// 	// ceil_diff = 1;
			// if (check_portal_ceiling_difference(current_portal, portal_behind))
				// floor_diff = 1;
			// if (ceil_diff && floor_diff)
			// 	generate_two_new_walls(current_portal, portal_behind);
			// if (floor_diff && !ceil_diff)
			// 	generate_a_new_wall(current_portal, portal_behind, 'c');
			// if (!floor_diff && ceil_diff)
			// 	generate_a_new_wall(current_portal, portal_behind, 'g');
		}
		current_portal = current_portal->next;
		i++;
	}
}
