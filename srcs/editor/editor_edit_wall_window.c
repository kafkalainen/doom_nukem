/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_edit_wall_window.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:58:06 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/24 14:50:58 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	convert_to_windowed_wall(t_editor_walls *wall, t_editor_sector *sector, t_editor_sector **head)
{
	t_editor_walls	*temp_wall;
	t_editor_sector *temp;
	t_xy			midpoint;
	t_xy			dir;

	midpoint.w = 0.0f;
	get_midpoint_of_walls(sector, wall->idx, (int *)&midpoint.x, (int *)&midpoint.y);
	dir.w = 0.0f;
	dir.x = -wall->norm.x;
	dir.y = -wall->norm.y;
	temp = *head;

	while (temp)
	{
		if (temp->idx_sector != sector->idx_sector)
		{
			temp_wall = get_intersecting_wall(temp, temp->nb_of_walls, dir, midpoint);
			if (temp_wall)
				break;
		}
		temp = temp->next;
	}
	if (temp_wall)
	{
		if (temp_wall->height.ground == wall->height.ground
			&& temp_wall->height.ceiling == wall->height.ceiling
			&& temp_wall->next->height.ground == wall->next->height.ground
			&& temp_wall->next->height.ceiling == wall->next->height.ceiling)
		{
			wall->type = -wall5;
			temp_wall->type = -wall5;
			return (true);
		}
	}
	return (false);
}