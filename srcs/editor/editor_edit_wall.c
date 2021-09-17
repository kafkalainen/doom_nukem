/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_edit_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:31:05 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/17 16:18:45 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static	void	change_wall_texture(int	*wall_type, t_action *action)
{
	if (*wall_type < 0)
	{
		if (*wall_type == -wall0)
			*wall_type = -wall1;
		else if (*wall_type == -wall1)
			*wall_type = -wall2;
		else if (*wall_type == -wall2)
			*wall_type = -wall3;
		else if (*wall_type == -wall3)
			*wall_type = -wall4;
		else if (*wall_type == -wall4)
			*wall_type = -wall5;
		else if (*wall_type == -wall5)
			*wall_type = -wall6;
		else if (*wall_type == -wall6)
			*wall_type = -wall7;
		else if (*wall_type == -wall7)
			*wall_type = -wall8;
		else if (*wall_type == -wall8)
			*wall_type = -wall9;
		else if (*wall_type == -wall9)
			*wall_type = -wall0;
	}
	action->change_wall_texture = 0;
	action->edit_wall = 0;
}

static void set_new_ceiling_ground(t_height *height,
	unsigned char **int_string, t_action *action)
{
	int temp;

	temp = ft_atoi((const char *)*int_string);
	if (temp > 99)
		temp = 99;
	if (temp < -99)
		temp = -99;
	if (action->edit_ceiling_height)
	{
		if (temp > height->ground)
			height->ceiling = temp;
	}
	if (action->edit_floor_height)
	{
		if (temp < height->ceiling)
			height->ground = temp;
	}
}

static void handle_wall_height(t_height *height,
	unsigned char **int_string, t_action *action)
{
	if (*int_string)
		set_new_ceiling_ground(height, int_string, action);
	if (*int_string)
		free(*int_string);
	*int_string = NULL;
	action->edit_wall = 0;
	action->edit_ceiling_height = 0;
	action->edit_floor_height = 0;
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
			handle_wall_height(&editor->temp_wall->height, &editor->int_string,
				&editor->action);
	}
	if (editor->action.change_wall_texture)
		change_wall_texture(&editor->temp_wall->type, &editor->action);
	if (editor->action.create_light_button || editor->action.create_powerstation
		|| editor->action.create_elev_button)
		create_entities(editor);
}
