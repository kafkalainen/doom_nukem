/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grid_events2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:37:12 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/02 14:03:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	check_for_objects_inside_sector_bbox(t_editor *editor)
{
	editor->action.draw_depth = sector;
	editor->action.prev_entity = editor->action.selected_entity;
	editor->temp_entity = get_clicked_entity(&editor->entity_list,
			editor->action.world_pos, &editor->action.selected_entity);
	editor->temp_wall = get_clicked_wall(&editor->temp_sector->walls,
			editor->action.world_pos, &editor->action.selected_wall,
			editor->temp_sector->nb_of_walls);
	if (editor->temp_entity)
		editor->action.draw_depth = entity;
	else if (editor->temp_wall)
		editor->action.draw_depth = wall;
}

t_bool	check_for_valid_map_range(t_xy pos)
{
	if (pos.x > -5000 && pos.x < 5000
		&& pos.y > -5000 && pos.y < 5000)
		return (true);
	return (false);
}
