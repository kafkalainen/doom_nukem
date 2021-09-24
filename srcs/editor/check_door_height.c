/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_door_height.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 11:10:25 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/24 12:26:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_bool	check_if_slanted_doorway(t_editor_walls *doorway,
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

t_bool	check_door_height(t_editor *editor, t_editor_walls *way,
		t_editor_sector *current)
{
	t_editor_sector	*sector;
	t_editor_walls	*way_2;
	int				height;

	sector = get_editor_sector_with_idx(&editor->sector_list,
			get_portal_idx(way->type));
	way_2 = get_editor_wall_with_type(&sector->walls, sector->nb_of_walls,
			current->idx_sector);
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

t_bool	check_legal_doors(t_editor *editor, t_editor_sector *sector)
{
	t_editor_walls	*wall;
	int				i;

	i = 0;
	wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (wall->type > 2999)
		{
			if (!check_door_height(editor, wall, sector))
				return (false);
		}
		wall = wall->next;
		i++;
	}
	return (true);
}
