/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:23:11 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/09 12:33:11 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_editor_sector	*get_clicked_sector(t_editor_sector **list, t_xy click,
				int *selected_sector)
{
	t_editor_sector	*temp;

	temp = *list;
	while (temp != NULL)
	{
		if (check_bbox(temp->bbox.start, temp->bbox.end, click))
		{
			*selected_sector = temp->idx_sector;
			return (temp);
		}
		temp = temp->next;
	}
	*selected_sector = -1;
	return (NULL);
}

t_editor_walls	*get_clicked_wall(t_editor_walls **walls, t_xy click,
				int *selected_wall, int nbr_of_walls)
{
	t_editor_walls	*temp;
	int				i;

	i = 0;
	temp = *walls;
	while (temp != NULL && i < nbr_of_walls)
	{
		if (check_bbox(temp->bbox.start, temp->bbox.end, click))
		{
			*selected_wall = temp->idx;
			return (temp);
		}
		i++;
		temp = temp->next;
	}
	*selected_wall = -1;
	return (NULL);
}

int		handle_events(t_editor *editor, t_home *home)
{
	if (editor->action.unlink_entity)
	{
		unlink_selected_entity(&editor->entity_list,
			editor->action.selected_entity, &editor->action.unlink_entity);
	}
	if (editor->action.create_sector)
	{
		create_new_sector(&editor->sector_list, &editor->action);
		editor->action.create_sector = 0;
		editor->action.edit_sector = 1;
	}
	if (editor->action.save_file)
		save_editor_map(editor, home);
	if (editor->action.input_active && editor->action.edit_sector)
	{
		handle_sector(&editor->sector_list, &editor->mouse_data, &editor->action);
	}
	if (editor->action.create_entity == 2)
	{
		create_new_entity(&editor->entity_list, &editor->mouse_data,
			&editor->action, editor->temp_sector);
		editor->action.create_entity = 0;
	}
	if (editor->mouse_data.i_mbleft)
	{
		if (clicked_inside_ui(editor->mouse_data.x, editor->mouse_data.y,
				editor->buffer.height, editor->buffer.width))
			check_ui_events(editor->mouse_data.x, editor->mouse_data.y,
				&editor->button_list, &editor->action);
		else if (clicked_inside_grid(editor->mouse_data.x, editor->mouse_data.y,
				editor->buffer.height, editor->buffer.width))
			check_grid_events(editor);
	}
	if (editor->action.link_maps == 2)
		link_maps(&editor->action, &editor->linked_mapname, editor->map_names);
	if (editor->action.unlink_maps)
	{
		if (editor->linked_mapname)
		{
			free(editor->linked_mapname);
			editor->linked_mapname = NULL;
		}
		editor->action.unlink_maps = 0;
	}
	if (editor->action.open_file == 2)
		editor_load_map(editor);
	return (1);
}
