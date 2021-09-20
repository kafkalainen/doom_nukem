/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:23:11 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/20 13:12:58 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	update_sector_light_values(t_editor_sector *sector,
		t_entity_list **head)
{
	t_entity_list	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (temp->sector_idx == sector->idx_sector && temp->entity_type == lamp)
		{
			sector->light.pos.x = temp->pos.x;
			sector->light.pos.y = temp->pos.y;
			sector->light.state = temp->state;
			break ;
		}
		temp = temp->next;
	}
}

void	editor_set_all_sector_floor_heights(t_editor_sector *sector,
	unsigned char **int_string)
{
	int				floor_height;
	t_editor_walls	*wall;
	int				i;

	i = 0;
	wall = sector->walls;
	floor_height = ft_atoi((const char *)*int_string);
	if (floor_height > 99)
		floor_height = 99;
	if (floor_height < -99)
		floor_height = -99;
	free(*int_string);
	*int_string = NULL;
	while (i < sector->nb_of_walls)
	{
		if (wall->height.ceiling > floor_height)
			wall->height.ground = floor_height;
		wall = wall->next;
		i++;
	}
}

void	editor_set_all_sector_ceiling_heights(t_editor_sector *sector,
	unsigned char **int_string)
{
	int				ceiling_height;
	t_editor_walls	*wall;
	int				i;

	i = 0;
	wall = sector->walls;
	ceiling_height = ft_atoi((const char *)*int_string);
	if (ceiling_height > 99)
		ceiling_height = 99;
	if (ceiling_height < -99)
		ceiling_height = -99;
	free(*int_string);
	*int_string = NULL;
	while (i < sector->nb_of_walls)
	{
		if (wall->height.ground < ceiling_height)
			wall->height.ceiling = ceiling_height;
		wall = wall->next;
		i++;
	}
}

void	editor_edit_sector(t_editor *editor)
{
	t_editor_sector	*sector;

	sector = editor->temp_sector;
	if (editor->action.change_ceiling_texture)
	{
		if (sector->tex_ceil == -surf0)
			sector->tex_ceil = -surf1;
		else if (sector->tex_ceil == -surf1)
			sector->tex_ceil = -surf2;
		else if (sector->tex_ceil == -surf2)
			sector->tex_ceil = -surf3;
		else if (sector->tex_ceil == -surf3)
			sector->tex_ceil = -surf4;
		else if (sector->tex_ceil == -surf4)
			sector->tex_ceil = -surf5;
		else if (sector->tex_ceil == -surf5)
			sector->tex_ceil = -surf6;
		else if (sector->tex_ceil == -surf6)
			sector->tex_ceil = -surf7;
		else if (sector->tex_ceil == -surf7)
			sector->tex_ceil = -surf8;
		else if (sector->tex_ceil == -surf8)
			sector->tex_ceil = -surf9;
		else if (sector->tex_ceil == -surf9)
			sector->tex_ceil = -surf0;
		editor->action.change_ceiling_texture = 0;
		editor->action.edit_sector = 0;
	}
	if (editor->action.change_floor_texture)
	{
		if (sector->tex_floor == -surf0)
			sector->tex_floor = -surf1;
		else if (sector->tex_floor == -surf1)
			sector->tex_floor = -surf2;
		else if (sector->tex_floor == -surf2)
			sector->tex_floor = -surf3;
		else if (sector->tex_floor == -surf3)
			sector->tex_floor = -surf4;
		else if (sector->tex_floor == -surf4)
			sector->tex_floor = -surf5;
		else if (sector->tex_floor == -surf5)
			sector->tex_floor = -surf6;
		else if (sector->tex_floor == -surf6)
			sector->tex_floor = -surf7;
		else if (sector->tex_floor == -surf7)
			sector->tex_floor = -surf8;
		else if (sector->tex_floor == -surf8)
			sector->tex_floor = -surf9;
		else if (sector->tex_floor == -surf9)
			sector->tex_floor = -surf0;
		editor->action.change_floor_texture = 0;
		editor->action.edit_sector = 0;
	}
	if (editor->action.set_light_intensity)
	{
		read_input_string(&editor->int_string, &editor->action);
		if (!editor->action.input_active)
		{
			if (editor->int_string)
			{
				sector->light.intensity = ft_atoi(
						(const char *)editor->int_string);
				if (sector->light.intensity > 100)
					sector->light.intensity = 100;
				if (sector->light.intensity < 0)
					sector->light.intensity = 0;
				free(editor->int_string);
				editor->int_string = NULL;
			}
			editor->action.set_light_intensity = 0;
			editor->action.edit_sector = 0;
		}
	}
	if (editor->action.write_sector_story)
	{
		read_input_string(&sector->plot_line, &editor->action);
		if (!editor->action.input_active)
		{
			editor->action.write_sector_story = 0;
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
	if (editor->action.create_elevator)
	{
		if (check_elevator_prerequisites(&editor->entity_list,
				&editor->sector_list, &editor->action))
			convert_sector_to_lift(editor->temp_sector, &editor->entity_list);
		editor->action.create_elevator = 0;
		editor->action.edit_sector = 0;
	}
	if (editor->action.set_all_sector_ceiling_heights)
	{
		read_input_string(&editor->int_string, &editor->action);
		if (!editor->action.input_active)
		{
			if (editor->int_string)
				editor_set_all_sector_ceiling_heights(editor->temp_sector,
					&editor->int_string);
			editor->action.set_all_sector_ceiling_heights = 0;
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
					&editor->int_string);
			editor->action.set_all_sector_floor_heights = 0;
			editor->action.edit_sector = 0;
		}
	}
}

int	handle_events(t_editor *editor, t_home *home)
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
