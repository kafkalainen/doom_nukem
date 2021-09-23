/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_update_entity_values.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:31:59 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/22 18:02:57 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_bool	entity_is_wall_bound(t_entity_list *entity)
{
	if (entity->entity_type == light_button
		|| entity->entity_type == lift_button
		|| entity->entity_type == powerstation)
		return (true);
	return (false);
}

static t_bool	entity_is_free_placed(t_entity_list *entity)
{
	if (entity->entity_type == skull_skulker
		|| entity->entity_type == thing
		|| entity->entity_type == drone
		|| entity->entity_type == crewmember
		|| entity->entity_type == ammo_pack
		|| entity->entity_type == keycard_cleaning
		|| entity->entity_type == keycard_engineering
		|| entity->entity_type == keycard_military)
		return (true);
	return (false);
}

static void	compare_midpoints_and_update_elevation(t_entity_list *ent,
	t_editor_sector *sector)
{
	t_editor_walls	*wall;
	int				i;
	t_screen_xy		midpoint;

	i = 0;
	midpoint = (t_screen_xy){0, 0};
	wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		get_midpoint_of_walls(sector, wall->idx, &midpoint.x, &midpoint.y);
		if (midpoint.x == ent->pos.x && midpoint.y == ent->pos.z)
		{
			ent->pos.y = get_selected_floor_height(sector, wall->idx) + 1;
			break ;
		}
		wall = wall->next;
		i++;
	}
}

void	update_all_entity_heights(t_editor *editor)
{
	t_entity_list	*ent;
	t_editor_sector	*temp_sector;

	ent = editor->entity_list;
	while (ent)
	{
		temp_sector = get_editor_sector_with_idx(&editor->sector_list,
				ent->sector_idx);
		if (temp_sector)
		{
			if (entity_is_wall_bound(ent))
				compare_midpoints_and_update_elevation(ent, temp_sector);
			else if (entity_is_free_placed(ent))
				ent->pos.y = get_highest_floor_height(&temp_sector->walls,
						temp_sector->nb_of_walls);
		}
		ent = ent->next;
	}
}
