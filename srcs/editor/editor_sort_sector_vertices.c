/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_sort_sector_vertices.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:13:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/09 17:30:04 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_bool	compare_points(t_editor_walls *wall, t_editor_walls *next)
{
	if (wall->center_angle < next->center_angle)
		return (true);
	else
	{
		if (wall->center_angle == next->center_angle
			&& wall->dist_from_center < next->dist_from_center)
			return (true);
	}
	return (false);
}

static void	calculate_angles_and_distances(t_editor_sector *sector)
{
	int				i;
	t_editor_walls	*cur_wall;
	t_xy			y_axis;

	cur_wall = sector->walls;
	y_axis = vec2(0.0f, 1.0f);
	while (i < sector->nb_of_walls)
	{
		cur_wall->centroid_vec = vec2_add(sector->centroid, vec2(cur_wall->x0.x,
			cur_wall->x0.y));
		cur_wall->centroid_vec = vec2_unit_vector(cur_wall->centroid_vec);
		cur_wall->center_angle = vec2_ang(cur_wall->centroid_vec, y_axis);
		cur_wall->dist_from_center = vec2_eucl_dist(sector->centroid, vec2(cur_wall->x0.x,
			cur_wall->x0.y));
		cur_wall = cur_wall->next;
		i++;
	}
}

void	editor_sort_wall_vertices(t_editor_sector *sector)
{
	int				i;
	int				j;
	t_editor_walls	*swap;
	t_editor_walls	*head;
	t_editor_walls	*temp;
	t_editor_walls	*temp2;

	(void)head;
	calculate_angles_and_distances(sector);
	temp = sector->walls;
	temp2 = sector->walls;
	head = sector->walls;
	j = 0;
	while (j < sector->nb_of_walls)
	{
		i = 0;
		temp = temp2;
		while (i < sector->nb_of_walls && compare_points(temp, temp->next))
		{
			temp = temp->next;
			i++;
		}
		if (i != sector->nb_of_walls)
		{
			swap = temp->next;
			temp->next = temp;
			temp = swap;
		}
		else
		{
			temp2 = temp2->next;
			j++;
		}
	}
}
