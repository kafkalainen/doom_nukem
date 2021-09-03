/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_lift.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:23:37 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 20:36:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	update_heights(t_home *home, t_sector *lift,
			t_wall *portal, t_wall *portal_behind)
{
	float	height_diff;

	if (portal->bottom.p[0].y != portal_behind->bottom.p[0].y)
		height_diff = portal_behind->bottom.p[0].y - portal->bottom.p[0].y;
	translate_entities(home, height_diff, lift->idx_sector);
	translate_sector(lift, height_diff);
}

Uint32	lock_lift(t_home *home, t_sector *lift)
{
	Uint32	i;
	t_wall	*cur_wall;
	t_wall	*portal;

	i = 0;
	cur_wall = lift->walls;
	while (i < lift->nb_of_walls)
	{
		if (cur_wall->top.idx >= 0
			&& home->sectors[cur_wall->top.idx]->is_lift == lift->lift_dir)
		{
			portal = get_portal_by_idx(lift->idx_sector,
					home->sectors[cur_wall->top.idx]);
			update_heights(home, lift, cur_wall, portal);
		}
		cur_wall = cur_wall->next;
		i++;
	}
	bolt_lift_door(lift, home->sectors, lift->lift_dir, unlocked);
	return (1);
}
