/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grid_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:44:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 09:22:21 by jnivala          ###   ########.fr       */
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

static void	reset_sector_light_info(t_editor_sector *sector, t_entity_list **entities)
{
	t_entity_list *linked_entity;

	if (sector->light.is_linked > 1)
	{
		ft_putendl("was linked");
		linked_entity = get_linked_entity(entities, sector->light.is_linked);
		linked_entity->is_linked = 0;
	}
	sector->light.intensity = 0;
	sector->light.is_linked = 0;
	sector->light.state = 0;
	sector->light.pos = (t_screen_xy){-1.0f, -1.0f};
}

static void	handle_delete(t_editor *editor)
{
	if (editor->action.selected_entity >= 0)
	{
		if (editor->temp_entity->entity_type == lamp)
		{
			ft_putendl("Deleted a lamp");
			reset_sector_light_info(editor->temp_sector, &editor->entity_list);
		}
		delete_selected_entity(&editor->entity_list, &editor->action);
		editor->temp_entity = NULL;
		editor->temp_sector = NULL;
		editor->action.selected_sector = -1;
		editor->action.draw_depth = depth_zero;
		add_notification(editor, "Removed entity.", 2000);
	}
	else if (editor->action.selected_sector >= 0)
	{
		editor_free_selected_sector(&editor->sector_list,
			&editor->entity_list, &editor->action);
		editor->temp_sector = NULL;
		editor->action.draw_depth = depth_zero;
		add_notification(editor, "Removed sector.", 2000);
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
		handle_delete(editor);
	if (editor->action.convert_to_portal == user_input)
	{
		if (editor->temp_sector && editor->action.prev_sector != -1)
			create_portal_between_sectors(&editor->sector_list, &editor->action);
		editor->action.convert_to_portal = idle;
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
		link_entities(&editor->entity_list, &editor->sector_list, editor->action.world_pos, editor->action.prev_entity);
		editor->action.link_entity = idle;
	}
}
