/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:23:11 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/10 17:24:22 by rzukale          ###   ########.fr       */
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

void	editor_edit_wall(t_editor_walls *wall, t_action *action, t_editor_sector *sector)
{
	unsigned char	*temp;
	(void)sector;
	if (action->edit_ceiling_height)
	{
		temp = (unsigned char *)ft_itoa(wall->height.ceiling);
		read_input_string(&temp, action);
		if (temp == NULL)
			wall->height.ceiling = 0;
		else
			wall->height.ceiling = ft_atoi((const char *)temp);
		if (temp != NULL)
			ft_strdel((char **)&temp);
		if (wall->height.ceiling > 99)
			wall->height.ceiling = 99;
		if (wall->height.ceiling < -99)
			wall->height.ceiling = -99;
		
		if (!action->input_active)
		{
			action->edit_wall = 0;
			action->edit_ceiling_height = 0;
		}
		
	}
}

int		handle_events(t_editor *editor, t_home *home)
{
	if (editor->action.edit_entity)
		edit_entity(editor->temp_entity, &editor->action);
	if (editor->action.unlink_entity)
	{
		unlink_selected_entity(&editor->entity_list,
			editor->action.selected_entity, &editor->action.unlink_entity);
	}
	if (editor->action.edit_wall && editor->temp_wall != NULL && editor->temp_sector != NULL)
		editor_edit_wall(editor->temp_wall, &editor->action, editor->temp_sector);
	if (editor->action.create_sector == allocate)
	{
		editor_create_new_sector(&editor->sector_list, &editor->action);
		editor->action.create_sector++;
	}
	if (editor->action.create_sector == user_input)
		editor_new_sector_wallpoints(&editor->sector_list,
			&editor->mouse_data, &editor->action);
	if (editor->action.save_file)
		save_editor_map(editor, home);
	if (editor->action.create_entity == user_input)
	{
		create_new_entity(&editor->entity_list, &editor->action,
			editor->temp_sector);
		editor->action.create_entity = idle;
	}
	if (editor->mouse_data.i_mbleft)
	{
		if (clicked_inside_ui(editor->mouse_data.x, editor->mouse_data.y,
				editor->buffer.height, editor->buffer.width))
		{
			check_ui_events(editor->mouse_data.x, editor->mouse_data.y,
				&editor->button_list, &editor->action);
			editor->mouse_data.i_mbleft = 0;
		}		
		else if (clicked_inside_grid(editor->mouse_data.x, editor->mouse_data.y,
				editor->buffer.height, editor->buffer.width))
		{
			check_grid_events(editor);
			editor->mouse_data.i_mbleft = 0;
		}
			
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
