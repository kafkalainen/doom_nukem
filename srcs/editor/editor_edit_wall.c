/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_edit_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:31:05 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/27 09:01:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	set_new_ceiling_ground(t_height *height, t_uchar **int_string,
			t_action *action, t_editor *editor)
{
	int				input_value;
	int				temp;

	input_value = ft_atoi((const char *)*int_string);
	snap_to_range(&input_value);
	if (action->edit_ceiling_height)
	{
		if (input_value > height->ground)
		{
			temp = height->ceiling;
			height->ceiling = input_value;
			validate_door_size(editor, &height->ceiling, temp);
		}
	}
	if (action->edit_floor_height)
	{
		if (input_value < height->ceiling)
		{
			temp = height->ground;
			height->ground = input_value;
			validate_door_size(editor, &height->ground, temp);
		}
	}
}

static void	handle_wall_height(t_editor *editor)
{
	if (editor->int_string)
		set_new_ceiling_ground(&editor->temp_wall->height, &editor->int_string,
			&editor->action, editor);
	if (editor->int_string)
		free(editor->int_string);
	editor->int_string = NULL;
	editor->action.edit_wall = 0;
	editor->action.edit_ceiling_height = 0;
	editor->action.edit_floor_height = 0;
}

static void	create_entities(t_editor *editor)
{
	if (editor->action.create_light_button)
	{
		if (entity_creation_is_allowed(&editor->entity_list,
				editor->temp_sector, &editor->action))
			create_new_entity(&editor->entity_list, &editor->action,
				editor->temp_sector, editor->temp_sector->centroid);
		editor->action.create_light_button = 0;
	}
	if (editor->action.create_powerstation)
	{
		if (entity_creation_is_allowed(&editor->entity_list,
				editor->temp_sector, &editor->action))
			create_new_entity(&editor->entity_list, &editor->action,
				editor->temp_sector, editor->temp_sector->centroid);
		editor->action.create_powerstation = 0;
	}
	if (editor->action.create_elev_button)
	{
		if (entity_creation_is_allowed(&editor->entity_list,
				editor->temp_sector, &editor->action))
			create_new_entity(&editor->entity_list, &editor->action,
				editor->temp_sector, editor->temp_sector->centroid);
		editor->action.create_elev_button = 0;
	}
	editor->action.edit_wall = 0;
}

void	editor_edit_wall(t_editor *editor)
{
	if (editor->action.edit_ceiling_height || editor->action.edit_floor_height)
	{
		read_input_string(&editor->int_string, &editor->action);
		if (!editor->action.input_active)
			handle_wall_height(editor);
	}
	if (editor->action.change_wall_texture)
		editor->action.edit_wall = change_wall_texture(&editor->temp_wall->type,
				&editor->action);
	if (editor->action.create_light_button || editor->action.create_powerstation
		|| editor->action.create_elev_button)
		create_entities(editor);
	if (editor->action.cycle_door)
	{
		if (!check_door_height(editor, editor->temp_wall,
				editor->temp_sector))
			editor->action.cycle_door = false;
		else
			editor->action.cycle_door = cycle_door(&editor->sector_list,
					editor->temp_wall, editor->temp_sector->idx_sector);
	}
}
