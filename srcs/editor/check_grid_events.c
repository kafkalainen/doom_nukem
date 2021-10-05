/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grid_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:44:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/05 14:57:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	setup_selected_sector_draw_depth(t_editor *editor)
{
	if (editor->temp_sector)
		check_for_objects_inside_sector_bbox(editor);
	if (!editor->temp_wall && !editor->temp_entity)
	{
		editor->temp_sector = get_clicked_sector(&editor->sector_list,
				editor->action.world_pos, &editor->action.selected_sector);
		if (editor->temp_sector)
			check_for_objects_inside_sector_bbox(editor);
	}
}

static void	reset_sector_light_info(t_entity_list **entities,
			t_editor_sector **sectors, t_entity_list *deleted_entity,
			t_editor_sector *sector)
{
	if (deleted_entity->is_linked > 1)
		unlink_linked_light_links(entities, sectors, deleted_entity);
	sector->light.intensity = 0;
	sector->light.is_linked = 0;
	sector->light.state = 0;
	sector->light.pos = (t_screen_xy){-1.0f, -1.0f};
}

static void	handle_delete(t_editor *editor)
{
	if (editor->action.selected_entity >= 0
		&& editor->action.selected_sector >= 0
		&& editor->temp_sector && editor->temp_entity)
	{
		if (editor->temp_entity->type == lamp)
			reset_sector_light_info(&editor->entity_list, &editor->sector_list,
				editor->temp_entity, editor->temp_sector);
		delete_selected_entity(&editor->entity_list, &editor->action);
		editor->action.selected_entity = -1;
		editor->temp_entity = NULL;
		editor->action.draw_depth = sector;
		add_notification(editor, "Removed entity.", 2000);
	}
	else if (editor->action.selected_sector >= 0 && editor->temp_sector)
	{
		editor_reset_player_and_end(editor, &editor->action);
		editor_free_selected_sector(&editor->sector_list,
			&editor->entity_list, &editor->action);
		if (editor->plr.sector >= 0 || editor->end_sector.sector >= 0)
			verify_plr_start_end_sector_coordinates(&editor->plr,
				&editor->sector_list, &editor->end_sector);
		add_notification(editor, "Removed sector.", 2000);
		sector_delete_helper(editor);
	}
	editor->action.delete = 0;
}

static void	check_grind_events_two(t_editor *editor)
{
	if (editor->action.assign_player_start == user_input)
		editor->action.player_start_assigned
			= assign_player_start(&editor->sector_list,
				&editor->action.world_pos, &editor->plr,
				&editor->action.assign_player_start);
	if (editor->action.link_entity == user_input
		&& editor->action.prev_entity != -1 && editor->temp_entity != NULL)
	{
		if (link_entities(&editor->entity_list, &editor->sector_list,
				editor->action.world_pos, editor->action.prev_entity))
			add_notification(editor, "Link successful", 2000);
		else
			add_notification(editor, "Linking failed.", 2000);
		editor->action.link_entity = idle;
	}
	if (editor->action.create_entity == user_input)
	{
		if (entity_creation_is_allowed(&editor->entity_list,
				editor->temp_sector, &editor->action))
			create_new_entity(&editor->entity_list, &editor->action,
				editor->temp_sector, editor->action.world_pos);
		editor->action.create_entity = idle;
	}
	editor->mouse_data.i_mbleft = 0;
}

void	check_grid_events(t_editor *editor)
{
	setup_selected_sector_draw_depth(editor);
	if (!editor->temp_sector)
		reset_actions(&editor->action);
	if (editor->action.delete
		&& (editor->action.selected_entity >= 0
			|| editor->action.selected_sector >= 0))
		handle_delete(editor);
	if (editor->action.convert_to_portal == user_input)
	{
		if (editor->temp_sector && editor->action.prev_sector != -1)
		{
			if (create_portal_between_sectors(&editor->sector_list,
					&editor->action))
				add_notification(editor, "Created successfully", 3000);
			else
				add_notification(editor, "ERROR: Could not create", 3000);
		}
		editor->action.convert_to_portal = idle;
	}
	if (editor->action.assign_end_sector == user_input)
		assign_end_sector(&editor->sector_list, &editor->action.world_pos,
			&editor->end_sector, &editor->action.assign_end_sector);
	check_grind_events_two(editor);
}
