/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grid_events2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:37:12 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/17 16:37:30 by rzukale          ###   ########.fr       */
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
