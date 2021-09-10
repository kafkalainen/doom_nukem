/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_sort_sector_vertices.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:13:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/10 08:39:16 by jnivala          ###   ########.fr       */
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

static void	sort_list(t_editor_walls **head, int nb_of_walls)
{
	int				i;
	int				j;
	t_editor_walls	*current;
	t_editor_walls	*index;

	if (!*head)
		return ;
	current = *head;
	i = 0;
	while (i < nb_of_walls)
	{
		j = 0;
		index = current->next;
		while (j < nb_of_walls)
		{
			if (compare_points(current, index))
				swap_node_data(current, index);
			index = index->next;
			j++;
		}
		i++;
		current = current->next;
	}
}

void	editor_sort_wall_vertices(t_editor_sector *sector)
{
	calculate_angles_and_distances(sector);
	sort_list(&sector->walls, sector->nb_of_walls);
}
