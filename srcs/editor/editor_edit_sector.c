/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_edit_sector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:12:08 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/04 14:22:08 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	editor_edit_change_sector_floor_tex(t_editor *editor)
{
	if (editor->temp_sector->tex_floor == -surf0)
		editor->temp_sector->tex_floor = -surf1;
	else if (editor->temp_sector->tex_floor == -surf1)
		editor->temp_sector->tex_floor = -surf2;
	else if (editor->temp_sector->tex_floor == -surf2)
		editor->temp_sector->tex_floor = -surf3;
	else if (editor->temp_sector->tex_floor == -surf3)
		editor->temp_sector->tex_floor = -surf4;
	else if (editor->temp_sector->tex_floor == -surf4)
		editor->temp_sector->tex_floor = -surf5;
	else if (editor->temp_sector->tex_floor == -surf5)
		editor->temp_sector->tex_floor = -surf6;
	else if (editor->temp_sector->tex_floor == -surf6)
		editor->temp_sector->tex_floor = -surf7;
	else if (editor->temp_sector->tex_floor == -surf7)
		editor->temp_sector->tex_floor = -surf8;
	else if (editor->temp_sector->tex_floor == -surf8)
		editor->temp_sector->tex_floor = -surf9;
	else if (editor->temp_sector->tex_floor == -surf9)
		editor->temp_sector->tex_floor = -surf0;
	editor->action.change_floor_texture = 0;
	editor->action.edit_sector = 0;
}

static void	editor_edit_sector_light_intensity(t_editor *editor)
{
	read_input_string(&editor->int_string, &editor->action);
	if (!editor->action.input_active)
	{
		if (editor->int_string)
		{
			editor->temp_sector->light.intensity = ft_atoi(
					(const char *)editor->int_string);
			if (editor->temp_sector->light.intensity > 100)
				editor->temp_sector->light.intensity = 100;
			if (editor->temp_sector->light.intensity < 0)
				editor->temp_sector->light.intensity = 0;
			free(editor->int_string);
			editor->int_string = NULL;
		}
		editor->action.set_light_intensity = 0;
		editor->action.edit_sector = 0;
	}
}

static void	editor_sector_story_and_light(t_editor *editor)
{
	if (editor->action.write_sector_story)
	{
		read_input_string(&editor->temp_sector->plot_line, &editor->action);
		if (!editor->action.input_active)
		{
			editor->action.write_sector_story = false;
			editor->action.edit_sector = 0;
		}
	}
	if (editor->action.create_light_source)
	{
		if (entity_creation_is_allowed(&editor->entity_list,
				editor->temp_sector, &editor->action))
		{
			create_new_entity(&editor->entity_list, &editor->action,
				editor->temp_sector, editor->temp_sector->centroid);
			update_sector_light_values(editor->temp_sector,
				&editor->entity_list);
		}
		editor->action.create_light_source = 0;
		editor->action.edit_sector = 0;
	}
}

static void	editor_edit_sector_ceiling_floor_heights(t_editor *editor)
{
	if (editor->action.set_all_sector_ceiling_heights)
	{
		read_input_string(&editor->int_string, &editor->action);
		if (!editor->action.input_active)
		{
			if (editor->int_string)
				editor_set_all_sector_ceiling_heights(editor->temp_sector,
					&editor->int_string, editor);
			editor->action.set_all_sector_ceiling_heights = false;
			editor->action.edit_sector = 0;
		}
	}
	if (editor->action.set_all_sector_floor_heights)
	{
		read_input_string(&editor->int_string, &editor->action);
		if (!editor->action.input_active)
		{
			if (editor->int_string)
				editor_set_all_sector_floor_heights(editor->temp_sector,
					&editor->int_string, editor);
			editor->action.set_all_sector_floor_heights = false;
			editor->action.edit_sector = 0;
		}
	}
}

void	editor_edit_sector(t_editor *editor)
{
	if (editor->action.change_ceiling_texture)
		editor_edit_change_sector_ceiling_tex(editor);
	if (editor->action.change_floor_texture)
		editor_edit_change_sector_floor_tex(editor);
	if (editor->action.set_light_intensity)
		editor_edit_sector_light_intensity(editor);
	if (editor->action.write_sector_story || editor->action.create_light_source)
		editor_sector_story_and_light(editor);
	if (editor->action.create_elevator)
	{
		if (check_elevator_prerequisites(&editor->entity_list,
				&editor->sector_list, &editor->action))
		{
			convert_sector_to_lift(editor->temp_sector, &editor->entity_list);
			add_notification(editor, "Converted to lift", 3000);
		}
		editor->action.create_elevator = 0;
		editor->action.edit_sector = 0;
	}
	if (editor->action.set_all_sector_ceiling_heights
		|| editor->action.set_all_sector_floor_heights)
		editor_edit_sector_ceiling_floor_heights(editor);
	if (editor->action.set_gravity)
		editor_edit_gravity(editor);
}
