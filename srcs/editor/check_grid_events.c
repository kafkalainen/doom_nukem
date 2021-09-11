/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grid_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:44:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/11 14:18:51 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	setup_selected_sector_draw_depth(t_editor *editor)
{
	editor->temp_sector = get_clicked_sector(&editor->sector_list,
						editor->action.world_pos,
						&editor->action.selected_sector);
	if (editor->temp_sector)
	{
		editor->action.draw_depth = sector;
		editor->action.prev_entity = editor->action.selected_entity;
		editor->temp_entity = get_clicked_entity(&editor->entity_list,
							editor->action.world_pos,
							&editor->action.selected_entity);
		editor->temp_wall = get_clicked_wall(&editor->temp_sector->walls,
							editor->action.world_pos,
							&editor->action.selected_wall,
							editor->temp_sector->nb_of_walls);
		if (editor->temp_entity)
			editor->action.draw_depth = entity;
		else if (editor->temp_wall)
			editor->action.draw_depth = wall;
	}
}

void	check_grid_events(t_editor *editor)
{
	setup_selected_sector_draw_depth(editor);
	if (!editor->temp_sector)
		reset_actions(&editor->action);
	if (editor->action.delete
		&& (editor->action.selected_entity >= 0
			|| editor->action.selected_sector >= 0))
	{
		if (editor->action.selected_entity >= 0)
		{
			delete_selected_entity(&editor->entity_list, &editor->action);
			editor->temp_entity = NULL;
			editor->action.draw_depth = depth_zero;
		}
		else if (editor->action.selected_sector >= 0)
		{
			editor_free_selected_sector(&editor->sector_list,
				&editor->entity_list, &editor->action);
			editor->temp_sector = NULL;
			editor->action.draw_depth = depth_zero;
		}
	}
	if (editor->action.assign_player_start == user_input)
		editor->action.player_start_assigned
			= assign_player_start(&editor->sector_list, &editor->action.world_pos,
				&editor->plr, &editor->action.assign_player_start);
	if (editor->action.assign_end_sector == user_input)
		assign_end_sector(&editor->sector_list, &editor->action.world_pos,
			&editor->end_sector, &editor->action.assign_end_sector);
	if (editor->action.link_entity == user_input && editor->action.prev_entity != -1 && editor->temp_entity != NULL)
	{
		link_entities(&editor->entity_list, editor->action.world_pos, editor->action.prev_entity);
		editor->action.link_entity = idle;
	}
}
