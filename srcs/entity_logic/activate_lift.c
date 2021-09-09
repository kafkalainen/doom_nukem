/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activate_lift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:50:13 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/09 11:37:28 by jnivala          ###   ########.fr       */
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
		if (portal_behind->top.type == idx)
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
		if (portal->top.type >= 0
			&& home->sectors[portal->top.type]->is_lift == next_floor)
			return (portal_height_diff(portal, home->sectors[portal->top.type],
					sector_idx));
		portal = portal->next;
		j++;
	}
	return (0.0f);
}

void	bolt_lift_doors(t_sector *lift, Uint32 state)
{
	Uint32	j;
	t_wall	*portal;

	j = 0;
	portal = lift->walls;
	while (j < lift->nb_of_walls)
	{
		if (portal->top.type >= 0 && portal->is_door)
		{
			lock_the_door(portal, portal->next);
			portal->open_until = 0;
			portal->is_closed = 1;
			portal->is_locked = state;
		}
		portal = portal->next;
		j++;
	}
}

void	bolt_lift_door(t_sector *lift, t_sector **sectors,
		Uint32 next_floor, Uint32 state)
{
	Uint32	j;
	t_wall	*portal;

	j = 0;
	portal = lift->walls;
	while (j < lift->nb_of_walls)
	{
		if (portal->top.type >= 0 && portal->is_door
			&& sectors[portal->top.type]->is_lift == next_floor)
			portal->is_locked = state;
		portal = portal->next;
		j++;
	}
}

/*
**	Activate lift gets the height difference between the two
**	floors, and calculates how fast lift must travel to reach
**	that floor in ten seconds. It stores also the information about
**	whether we are going upwards or downwards.
*/
void	activate_lift(t_home *home, t_entity *entity, t_player *plr)
{
	float	height;

	if (entity->is_linked > 1)
	{
		if (home->sectors[entity->is_linked - 2]->moving_until < plr->time)
		{
			if (entity->state)
			{
				home->sectors[entity->is_linked - 2]->lift_dir = upper;
				height
					= get_floor_height_diff(home, entity->is_linked - 2, upper);
			}
			else
			{
				home->sectors[entity->is_linked - 2]->lift_dir = lower;
				height
					= get_floor_height_diff(home, entity->is_linked - 2, lower);
			}
			home->sectors[entity->is_linked - 2]->moving_until
				= plr->time + 10000;
			home->sectors[entity->is_linked - 2]->velocity = height * 0.1f;
			bolt_lift_doors(home->sectors[entity->is_linked - 2], locked);
			play_sound(plr->audio.lift, 20);
		}
	}
}
