/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sector_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 13:29:17 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/22 15:47:00 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	initialize_sector_pointers(t_sector *new_sector)
{
	new_sector->walls = NULL;
	new_sector->ceiling = NULL;
	new_sector->ground = NULL;
	new_sector->story = NULL;
}

void	initialize_triangles(t_wall *wall, t_point_data *left,
	t_point_data *right)
{
	wall->top.p[0] = (t_xyz){left->x, left->ground, left->y, 1.0f};
	wall->top.p[1] = (t_xyz){left->x, left->ceiling, left->y, 1.0f};
	wall->top.p[2] = (t_xyz){right->x, right->ceiling, right->y, 1.0f};
	wall->bottom.p[0] = (t_xyz){left->x, left->ground, left->y, 1.0f};
	wall->bottom.p[1] = (t_xyz){right->x, right->ceiling, right->y, 1.0f};
	wall->bottom.p[2] = (t_xyz){right->x, right->ground, right->y, 1.0f};
}

void	initialize_door(t_wall *wall, t_point_data *left, t_point_data *right)
{
	wall->top.idx = change_door_to_portal(left->idx);
	wall->bottom.idx = change_door_to_portal(left->idx);
	wall->is_door = 0;
	wall->is_closed = 0;
	wall->open_until = 0;
	wall->height = get_wall_height(left->ground, right->ground,
			left->ceiling, right->ceiling);
	if (left->idx >= DOOR_INDEX)
		wall->is_door = 1;
}

void	initialize_switches(t_wall *wall, t_point_data *left)
{
	wall->light_switch.is_switch = left->light_switch;
	wall->light_switch.on_off = 0;
	wall->station.is_health_station = left->health_station;
	wall->station.is_depleted = 0;
}

void	add_to_middle(t_wall **current_point, t_wall *new_wall)
{
	t_wall	*temp;

	if (new_wall == NULL)
		return ;
	if (*current_point == NULL)
	{
		*current_point = new_wall;
	}
	else
	{
		temp = (*current_point)->next;
		(*current_point)->next = new_wall;
		new_wall->next = temp;
	}
}
