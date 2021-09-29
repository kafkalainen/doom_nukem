/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:40:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/29 14:25:09 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	close_editor_wall_list(t_editor_walls **head)
{
	t_editor_walls	*temp;

	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = *head;
}

t_bool	check_for_last_point(t_editor_sector *sector, t_action *action)
{
	float	dist;

	if (!sector || !sector->walls)
		return (false);
	dist = vec2_eucl_dist(action->world_pos,
			vec2(sector->walls->x0.x, sector->walls->x0.y));
	if (dist <= 0.5f)
		return (true);
	return (false);
}

void	remove_last_point(t_editor_walls **walls, int *nb_of_walls)
{
	t_editor_walls	*previous;
	t_editor_walls	*deleted;

	previous = *walls;
	while (previous && previous->next && previous->next->next)
		previous = previous->next;
	deleted = previous->next;
	if (deleted == NULL)
		return ;
	free(deleted);
	deleted = NULL;
	previous->next = NULL;
	*nb_of_walls -= 1;
	return ;
}

static int	add_last_point(t_editor *editor, t_editor_sector *sector,
			t_action *action, t_editor_walls *point)
{
	point = sector->walls;
	while (point && point->next)
		point = point->next;
	if (check_all_sectors_for_intersecting_lines(&editor->sector_list,
			point->x0, sector->walls->x0))
		add_notification(editor, "ERROR: Cannot close, lines isecting.", 4000);
	else
	{
		close_editor_wall_list(&sector->walls);
		assign_sector_bbox(sector);
		if (check_if_non_convex(sector)
			|| check_if_another_sector_is_inside(sector, &editor->sector_list)
			|| check_if_completely_inside(sector, &editor->sector_list))
		{
			add_notification(editor, "ERROR: Non-convex or inside", 4000);
			return (3);
		}
		sector->centroid = editor_calculate_centroid(sector);
		action->selected_sector = -1;
		editor_sort_wall_vertices(sector);
		action->create_sector = idle;
		action->selected_wall = -1;
		editor->temp_wall = NULL;
	}
	return (0);
}

int	add_point_to_list(t_editor *editor, t_editor_sector *sector,
	t_action *action)
{
	t_editor_walls	*point;

	if (sector == NULL)
		return (1);
	point = sector->walls;
	if (sector->nb_of_walls > 1 && check_for_last_point(sector, action))
		return (add_last_point(editor, sector, action, point));
	while (point && point->next)
		point = point->next;
	if (point && check_all_sectors_for_intersecting_lines(
			&editor->sector_list, point->x0,
			round_coordinates(action->world_pos)))
		add_notification(editor, "ERROR: Cannot close, lines isecting.", 5000);
	else if (point && !check_for_valid_map_range(action->world_pos))
		add_notification(editor, "ERROR: Invalid range.", 2000);
	else
	{
		point = new_wall_point(round_coordinates(action->world_pos));
		if (point)
			add_point_end(&sector->walls, point);
		else
			error_output("Error while allocating wallpoints.");
		sector->nb_of_walls += 1;
	}
	return (0);
}
