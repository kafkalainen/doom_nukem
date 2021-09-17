/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:58:32 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/17 09:27:14 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_bool	initialize_int_string_logic(t_action *action)
{
	if (action->set_light_intensity
		|| action->edit_ceiling_height
		|| action->edit_floor_height
		|| action->set_all_sector_ceiling_heights
		|| action->set_all_sector_floor_heights)
		return (true);
	return (false);
}

void	draw_ui(t_editor *editor, t_texture **textures)
{
	if (editor->action.grid == 1)
		draw_grid(&editor->buffer, &editor->action);
	draw_editor_sectors_bboxes(editor, &editor->action);
	draw_editor_sectors(editor);
	draw_editor_entities(editor, textures);
	if (editor->action.link_entity == allocate)
		draw_entity_link_line(editor);
	if (editor->action.convert_to_portal)
		draw_convert_to_portal_line(editor);
	if (editor->action.save_file)
		draw_input_string(editor->mapname, &editor->buffer, map_saving);
	if (editor->action.open_file || editor->action.link_maps)
		update_editor_load_menu(&editor->buffer, &editor->action,
			editor->map_names);
	if (initialize_int_string_logic(&editor->action))
		draw_int_string_input(&editor->buffer, &editor->action,
			&editor->int_string);
	if (editor->action.write_sector_story && editor->temp_sector != NULL)
		draw_input_string(editor->temp_sector->plot_line,
			&editor->buffer, story_string);
	draw_help_text(&editor->action, &editor->buffer);
	show_editor_usage(&editor->buffer);
	notify_user(&editor->notification, &editor->buffer,
		editor->delta_time, &editor->notify_time);
}
