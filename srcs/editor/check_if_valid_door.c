/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_valid_door.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 11:10:25 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/06 18:39:33 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_if_slanted_doorway(t_editor_walls *doorway,
				t_editor_walls *doorway_2)
{
	if (doorway->height.ceiling != doorway->next->height.ceiling
		|| doorway->height.ground != doorway->next->height.ground)
		return (true);
	else if (doorway_2->height.ceiling != doorway_2->next->height.ceiling
		|| doorway_2->height.ground != doorway_2->next->height.ground)
		return (true);
	return (false);
}

t_bool	check_that_if_part_of_lift(t_sector *sector1, t_sector *sector2)
{
	if (sector1->is_lift == lift && sector2->is_lift == upper)
		return (true);
	else if (sector1->is_lift == lift && sector2->is_lift == lower)
		return (true);
	else if (sector2->is_lift == lift && sector1->is_lift == upper)
		return (true);
	else if (sector2->is_lift == lift && sector1->is_lift == lower)
		return (true);
	else
		return (false);
}

t_bool	check_if_valid_door(t_editor *editor, t_editor_walls *way,
		t_editor_sector *current)
{
	t_editor_sector	*sector;
	t_editor_walls	*way_2;
	int				height;

	sector = get_editor_sector_with_idx(&editor->sector_list,
			get_portal_idx(way->type));
	way_2 = get_editor_wall_with_type(&sector->walls, sector->nb_of_walls,
			current->idx_sector);
	if (editor->temp_sector && sector
		&& check_that_if_part_of_lift(editor->temp_sector, sector))
	{
		add_notification(editor, "This doorway is part of a lift.", 1500);
		return (false);
	}
	if (way && way_2 && check_if_slanted_doorway(way, way_2))
	{
		add_notification(editor, "Doorway slanted, cannot change.", 1500);
		return (false);
	}
	height = ft_imin(way->height.ceiling, way_2->height.ceiling)
		- ft_imax(way->height.ground, way_2->height.ground);
	if (height >= 2 && height < 5)
		return (true);
	add_notification(editor, "Door height must be between 2 and 4.", 1500);
	return (false);
}

void	validate_door_size(t_editor *editor, float *height, int val)
{
	t_editor_walls	*wall;

	if (!editor->temp_wall)
		return ;
	wall = get_previous_wall(editor->temp_wall, editor->temp_sector);
	if (editor->temp_wall->type > 2999
		&& !check_if_valid_door(editor, editor->temp_wall, editor->temp_sector))
		*height = val;
	if (wall && wall->type > 2999
		&& !check_if_valid_door(editor, wall, editor->temp_sector))
		*height = val;
}
