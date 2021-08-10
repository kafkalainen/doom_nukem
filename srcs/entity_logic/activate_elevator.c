/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activate_elevator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:50:13 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/10 16:49:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static float	portal_height_diff(t_wall *portal, t_sector *connection,
				int idx)
{
	Uint32	i;
	t_wall	*portal_behind;

	i = 0;
	portal_behind = connection->walls;
	while (i < connection->nb_of_walls)
	{
		if (portal_behind->top.idx == idx)
			return (portal_behind->bottom.p[0].y - portal->bottom.p[0].y);
		portal_behind = portal_behind->next;
		i++;
	}
	return (0.0f);
}

static float	get_floor_height_diff(t_home *home, int sector_idx,
				Uint32 next_floor)
{
	Uint32	j;
	t_wall	*portal;

	j = 0;
	portal = home->sectors[sector_idx]->walls;
	while (j < home->sectors[sector_idx]->nb_of_walls)
	{
		if (portal->top.idx >= 0
			&& home->sectors[portal->top.idx]->is_elevator == next_floor)
			return (portal_height_diff(portal, home->sectors[portal->top.idx],
					sector_idx));
		portal = portal->next;
		j++;
	}
	return (0.0f);
}

void	bolt_elevator_doors(t_sector *sector, Uint32 state)
{
	Uint32	j;
	t_wall	*portal;

	j = 0;
	portal = sector->walls;
	while (j < sector->nb_of_walls)
	{
		if (portal->top.idx >= 0 && portal->is_door)
			portal->is_locked = state;
		portal = portal->next;
		j++;
	}
}

/*
**	Activate elevator gets the height difference between the two
**	floors, and calculates how fast elevator must travel to reach
**	that floor in ten seconds. It stores also the information about
**	whether we are going upwards or downwards.
*/
void	activate_elevator(t_home *home, t_entity *entity, t_player *plr)
{
	float	height;

	if (entity->is_linked > 1)
	{
		if (home->sectors[entity->is_linked - 2]->moving_until < plr->time)
		{
			if (entity->state)
			{
				home->sectors[entity->is_linked - 2]->elevator_dir = upper;
				height
					= get_floor_height_diff(home, entity->is_linked - 2, upper);
			}
			else
			{
				home->sectors[entity->is_linked - 2]->elevator_dir = lower;
				height
					= get_floor_height_diff(home, entity->is_linked - 2, lower);
			}
			home->sectors[entity->is_linked - 2]->moving_until
				= plr->time + 10000;
			home->sectors[entity->is_linked - 2]->velocity
				= height * 0.1f;
			bolt_elevator_doors(home->sectors[entity->is_linked - 2], locked);
		}
	}
}
