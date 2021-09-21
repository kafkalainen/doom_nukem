/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:23:11 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/21 10:15:33 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static	void	unlink_maps(unsigned char **linked_map, t_action *action)
{
	if (*linked_map)
	{
		free(*linked_map);
		*linked_map = NULL;
	}
	action->unlink_maps = 0;
}

static void	handle_events_two(t_editor *editor, t_home *home)
{
	if (editor->action.save_file)
		save_editor_map(editor, home);
	if (editor->mouse_data.i_mbleft && !editor->action.input_active)
	{
		if (clicked_inside_ui(editor->mouse_data.x, editor->mouse_data.y,
				editor->buffer.height, editor->buffer.width))
		{
			check_ui_events(editor->mouse_data.x, editor->mouse_data.y,
				&editor->button_list, &editor->action);
			editor->mouse_data.i_mbleft = 0;
			if (editor->action.convert_to_portal == allocate
				&& editor->temp_sector)
				editor->action.prev_sector = editor->temp_sector->idx_sector;
		}
		else if (clicked_inside_grid(editor->mouse_data.x, editor->mouse_data.y,
				editor->buffer.height, editor->buffer.width))
			check_grid_events(editor);
	}
	if (editor->action.link_maps == 2)
		link_maps(&editor->action, &editor->linked_mapname, editor->map_names);
	if (editor->action.unlink_maps)
		unlink_maps(&editor->linked_mapname, &editor->action);
	if (editor->action.open_file == 2)
		editor_load_map(editor);
}

void	handle_events(t_editor *editor, t_home *home)
{
	editor->delta_time = SDL_GetTicks() - editor->cur_time;
	editor->cur_time = SDL_GetTicks();
	if (editor->action.edit_entity)
		edit_entity(&editor->action, editor->temp_entity, editor);
	if (editor->action.unlink_entity)
		unlink_linked_light_links(&editor->entity_list,
			&editor->sector_list, editor->temp_entity);
	if (editor->action.edit_wall && editor->temp_wall != NULL
		&& editor->temp_sector != NULL)
		editor_edit_wall(editor);
	if (editor->action.edit_sector && editor->temp_sector != NULL)
		editor_edit_sector(editor);
	if (editor->action.create_sector == allocate)
	{
		editor_create_new_sector(&editor->sector_list, &editor->action);
		editor->action.create_sector++;
	}
	if (editor->action.create_sector == user_input)
	{
		if (editor_new_sector_wallpoints(editor,
				&editor->mouse_data, &editor->action))
			editor_free_selected_sector(&editor->sector_list,
				&editor->entity_list, &editor->action);
	}
	handle_events_two(editor, home);
}
