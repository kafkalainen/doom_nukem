/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_elevator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:23:37 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/11 08:25:09 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	update_heights(t_home *home, t_sector *elevator,
			t_wall *portal, t_wall *portal_behind)
{
	float	height_diff;

	if (portal->bottom.p[0].y != portal_behind->bottom.p[0].y)
		height_diff = portal_behind->bottom.p[0].y - portal->bottom.p[0].y;
	translate_entities(home, height_diff, elevator->idx_sector);
	translate_sector(elevator, height_diff);
}

Uint32	lock_elevator(t_home *home, t_sector *elevator)
{
	Uint32	i;
	t_wall	*cur_wall;
	t_wall	*portal;

	i = 0;
	cur_wall = elevator->walls;
	while (i < elevator->nb_of_walls)
	{
		if (cur_wall->top.idx >= 0
			&& home->sectors[cur_wall->top.idx]->is_elevator
			== elevator->elevator_dir)
		{
			portal = get_portal_by_idx(elevator->idx_sector,
					home->sectors[cur_wall->top.idx]);
			update_heights(home, elevator, cur_wall, portal);
		}
		cur_wall = cur_wall->next;
		i++;
	}
	bolt_elevator_door(elevator, home->sectors, elevator->elevator_dir, unlocked);
	return (1);
}
