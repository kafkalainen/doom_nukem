/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_lift_doors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:02:11 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/04 08:34:16 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	generate_doors_to_portals(t_sector *original, t_sector **next,
			t_wall *portal)
{
	t_wall	*portal_behind;

	portal_behind = get_portal_by_idx(original->idx_sector,
			next[portal->top.idx]);
	portal->is_door = 1;
	portal_behind->is_door = 1;
	original->nb_of_walls += generate_doors(portal);
	next[portal->top.idx]->nb_of_walls += generate_doors(portal_behind);
}

void	calc_lift_doors(t_home *home)
{
	Uint32	i;
	Uint32	j;
	t_wall	*current_portal;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		j = 0;
		current_portal = home->sectors[i]->walls;
		while (home->sectors[i]->is_lift
			&& j < home->sectors[i]->nb_of_walls)
		{
			if (current_portal->top.idx >= 0 && !current_portal->is_door
				&& home->sectors[current_portal->top.idx]->is_lift)
				generate_doors_to_portals(home->sectors[i], home->sectors,
					current_portal);
			if (home->sectors[i]->is_lift == lift)
				current_portal->is_locked = unlocked;
			current_portal = current_portal->next;
			j++;
		}
		i++;
	}
}
