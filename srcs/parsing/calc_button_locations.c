/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_button_locations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:13:05 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/29 15:08:12 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	get_midpoint_of_wall(t_xy a, t_xy b, t_xyz *pos)
{
	t_xy	mid;

	if (a.x < b.x)
		mid.x = (b.x + a.x) * 0.5;
	else
		mid.x = (a.x + b.x) * 0.5;
	if (a.y < b.y)
		mid.y = (b.y + a.y) * 0.5;
	else
		mid.y = (a.y + b.y) * 0.5;
	mid.w = 0.0f;
	(*pos).x = mid.x;
	(*pos).z = mid.y;
}

static void	loop_walls(t_sector *sector, t_entity *entity)
{
	int		i;
	t_wall	*wall;

	i = 0;
	wall = sector->walls;
	while (i < (int)sector->nb_of_walls)
	{
		if (point_is_on_the_lseg(wall->point,
				(t_xy){entity->pos.x, entity->pos.z, 0.0f}, wall->next->point)
			|| (vec2_check_if_same_point(wall->next->point,
				(t_xy){entity->pos.x, entity->pos.z, 0.0f})))
			get_midpoint_of_wall(wall->point, wall->next->point, &entity->pos);
		i++;
		wall = wall->next;
	}
}

void	calc_button_locations(t_home *home)
{
	int		i;

	i = 0;
	while (i < (int)home->nbr_of_entities)
	{
		if (home->entity_pool[i]->type == light_button
			|| home->entity_pool[i]->type == lift_button
			|| home->entity_pool[i]->type == powerstation)
			loop_walls(home->sectors[home->entity_pool[i]->sector_idx],
				home->entity_pool[i]);
		i++;
	}
}
