/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:23:11 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/13 19:29:10 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	entity_creation_is_allowed(t_entity_list **head, t_editor_sector *sector, t_action *action)
{
	t_entity_list	*temp;
	t_editor_walls	*wall;
	int				i;

	temp = *head;
	wall = sector->walls;
	i = 0;
	while (i < sector->nb_of_walls)
	{
		if (action->selected_wall == wall->idx && wall->type >= 0)
			return (false);
		wall = wall->next;
		i++;
	}
	if (action->create_light_button) // only 1 allowed
	{
		while (temp != NULL)
		{
			if (temp->entity_type == light_button && temp->sector_idx == sector->idx_sector)
				return (false);
			temp = temp->next;
		}
	}
	if (action->create_light_source) // only 1 allowed
	{
		while (temp != NULL)
		{
			if (temp->entity_type == lamp && temp->sector_idx == sector->idx_sector)
				return (false);
			temp = temp->next;
		}
	}
	if (action->create_elev_button) // only 1 allowed
	{
		while (temp != NULL)
		{
			if (temp->entity_type == lift_button && temp->sector_idx == sector->idx_sector)
				return (false);
			temp = temp->next;
		}
	}
	// if (action->create_powerstation) // cannot create on top of something
	return (true);
}

void	editor_edit_wall(t_editor *editor)
{
	if (editor->action.edit_ceiling_height || editor->action.edit_floor_height)
	{
		read_input_string(&editor->int_string, &editor->action);
		if (!editor->action.input_active)
		{
			if (editor->action.edit_ceiling_height && editor->int_string)
			{
				editor->temp_wall->height.ceiling = ft_atoi((const char *)editor->int_string);
				if (editor->temp_wall->height.ceiling > 99)
					editor->temp_wall->height.ceiling = 99;
				if (editor->temp_wall->height.ceiling < -99)
					editor->temp_wall->height.ceiling = -99;
			}
			if (editor->action.edit_floor_height && editor->int_string)
			{
				editor->temp_wall->height.ground = ft_atoi((const char *)editor->int_string);
				if (editor->temp_wall->height.ground > 99)
					editor->temp_wall->height.ground = 99;
				if (editor->temp_wall->height.ground < -99)
					editor->temp_wall->height.ground = -99;
			}
			if (editor->int_string)
				free(editor->int_string);
			editor->int_string = NULL;
			editor->action.edit_wall = 0;
			editor->action.edit_ceiling_height = 0;
			editor->action.edit_floor_height = 0;
		}
	}
	if (editor->action.change_wall_texture)
	{
		if (editor->temp_wall->type < 0)
		{
			if (editor->temp_wall->type == -wall0)
				editor->temp_wall->type = -wall1;
			else if (editor->temp_wall->type == -wall1)
				editor->temp_wall->type = -wall2;
			else if (editor->temp_wall->type == -wall2)
				editor->temp_wall->type = -wall3;
			else if (editor->temp_wall->type == -wall3)
				editor->temp_wall->type = -wall4;
			else if (editor->temp_wall->type == -wall4)
				editor->temp_wall->type = -wall5;
			else if (editor->temp_wall->type == -wall5)
				editor->temp_wall->type = -wall6;
			else if (editor->temp_wall->type == -wall6)
				editor->temp_wall->type = -wall7;
			else if (editor->temp_wall->type == -wall7)
				editor->temp_wall->type = -wall8;
			else if (editor->temp_wall->type == -wall8)
				editor->temp_wall->type = -wall9;
			else if (editor->temp_wall->type == -wall9)
				editor->temp_wall->type = -wall0;
		}
		editor->action.change_wall_texture = 0;
		editor->action.edit_wall = 0;
	}
	if (editor->action.create_light_button)
	{
		if (entity_creation_is_allowed(&editor->entity_list, editor->temp_sector, &editor->action))
			create_new_entity(&editor->entity_list, &editor->action, editor->temp_sector, editor->temp_sector->centroid);
		editor->action.create_light_button = 0;
		editor->action.edit_wall = 0;
	}
	if (editor->action.create_powerstation)
	{
		if (entity_creation_is_allowed(&editor->entity_list, editor->temp_sector, &editor->action))
			create_new_entity(&editor->entity_list, &editor->action, editor->temp_sector, editor->temp_sector->centroid);
		editor->action.create_powerstation = 0;
		editor->action.edit_wall = 0;
	}
	if (editor->action.create_elev_button)
	{
		if (entity_creation_is_allowed(&editor->entity_list, editor->temp_sector, &editor->action))
			create_new_entity(&editor->entity_list, &editor->action, editor->temp_sector, editor->temp_sector->centroid);
		editor->action.create_elev_button = 0;
		editor->action.edit_wall = 0;
	}
}

void	update_sector_light_values(t_editor_sector *sector, t_entity_list **head)
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

t_bool	check_nbr_of_portals(t_editor_walls **walls, int nbr_of_walls)
{
	t_editor_walls	*wall;
	int				i;
	int				nbr_of_portals;

	i = 0;
	nbr_of_portals = 0;
	wall = *walls;
	while (i < nbr_of_walls)
	{
		if (wall->type >= 0)
			nbr_of_portals++;
		i++;
		wall = wall->next;
	}
	if (nbr_of_portals != 2)
		return (false);
	return (true);
}

t_bool	check_for_elevator_button(t_entity_list **head, int sector_idx)
{
	t_entity_list	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->sector_idx == sector_idx && temp->entity_type == lift_button)
			break ;
		temp = temp->next;
	}
	if (!temp)
		return (false);
	return (true);
}

void	get_lowest_floor_highest_ceiling(t_editor_sector *sector, int *height)
{
	t_editor_walls	*wall;
	int				i;

	i = 0;
	wall = sector->walls;
	*height = wall->height.ground;
	while (i < sector->nb_of_walls)
	{
		if (wall->height.ground < *height)
			*height = wall->height.ground;
		i++;
		wall = wall->next;
	}
}

t_bool	sectors_aligned(t_editor_sector *first, t_editor_sector *second, int first_height, int second_height)
{
	if (first_height == second_height)
		return (false);
	if (first_height > second_height)
	{
		first->is_elevator = upper;
		second->is_elevator = lower;
	}
	else
	{
		first->is_elevator = lower;
		second->is_elevator = upper;
	}
	return (true);
}

t_bool	compare_floors_to_ceilings(t_editor_sector **sectors, int first_idx, int second_idx)
{
	t_editor_sector	*first;
	t_editor_sector *second;
	int			floor_height_one;
	int			floor_height_two;

	first = *sectors;
	second = *sectors;
	while (first)
	{
		if (first->idx_sector == first_idx)
			break ;
		first = first->next;
	}
	if (!first)
		return (false);
	while (second)
	{
		if (second->idx_sector == second_idx)
			break ;
		second = second->next;
	}
	if (!second)
		return (false);
	get_lowest_floor_highest_ceiling(first, &floor_height_one);
	get_lowest_floor_highest_ceiling(second, &floor_height_two);
	if (!sectors_aligned(first, second, floor_height_one, floor_height_two))
		return (false);
	return (true);
}

t_bool	verify_connecting_sectors(t_editor_sector **sectors, t_editor_sector *elev_sector)
{
	t_editor_walls	*wall;
	int				i;
	int				first_sector_idx;
	int				scdn_sector_idx;
	int				nbr_of_portals;

	i = 0;
	nbr_of_portals = 0;
	wall = elev_sector->walls;
	while (i < elev_sector->nb_of_walls)
	{
		if (wall->type >= 0)
		{
			nbr_of_portals++;
			if (nbr_of_portals == 1)
				first_sector_idx = wall->type;
			else
				scdn_sector_idx = wall->type;
		}
		i++;
		wall = wall->next;
	}
	if (!compare_floors_to_ceilings(sectors, first_sector_idx, scdn_sector_idx))
		return (false);
	return (true);
}

t_bool	check_elevator_prerequisites(t_entity_list **head, t_editor_sector **sectors, t_action *action)
{
	t_editor_sector	*sector;

	sector = *sectors;
	while (sector)
	{
		if (sector->idx_sector == action->selected_sector)
			break ;
		sector = sector->next;
	}
	if (!sector)
		return (false);
	if (!check_nbr_of_portals(&sector->walls, sector->nb_of_walls))
		return (false);
	if (!check_for_elevator_button(head, sector->idx_sector))
		return (false);
	if (!verify_connecting_sectors(sectors, sector))
		return (false);
	return (true);
}

void	convert_sector_to_lift(t_editor_sector *sector, t_entity_list **head)
{
	t_entity_list	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->sector_idx == sector->idx_sector && temp->entity_type == lift_button)
			break ;
		temp = temp->next;
	}
	if (!temp)
		return ;
	temp->is_linked = upper;
	sector->is_elevator = lift;
	// connecting portals need to be modified to include door textures
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
				sector->light.intensity = ft_atoi((const char *)editor->int_string);
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
		if (entity_creation_is_allowed(&editor->entity_list, editor->temp_sector, &editor->action))
		{
			create_new_entity(&editor->entity_list, &editor->action, editor->temp_sector, editor->temp_sector->centroid);
			update_sector_light_values(editor->temp_sector, &editor->entity_list);
		}
		editor->action.create_light_source = 0;
		editor->action.edit_sector = 0;
	}
	if (editor->action.create_elevator)
	{
		if (check_elevator_prerequisites(&editor->entity_list, &editor->sector_list, &editor->action))
			convert_sector_to_lift(editor->temp_sector, &editor->entity_list);
		editor->action.create_elevator = 0;
		editor->action.edit_sector = 0;
	}
}

int		handle_events(t_editor *editor, t_home *home)
{
	editor->delta_time = SDL_GetTicks() - editor->cur_time;
	editor->cur_time = SDL_GetTicks();
	if (editor->action.edit_entity)
		edit_entity(editor->temp_entity, &editor->action, editor->temp_sector);
	if (editor->action.unlink_entity)
	{
		unlink_selected_entity(&editor->entity_list,
			editor->action.selected_entity, &editor->action.unlink_entity);
	}
	if (editor->action.edit_wall && editor->temp_wall != NULL && editor->temp_sector != NULL)
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
	if (editor->action.create_entity == user_input)
	{
		create_new_entity(&editor->entity_list, &editor->action,
			editor->temp_sector, editor->action.world_pos);
		editor->action.create_entity = idle;
	}
	if (editor->mouse_data.i_mbleft && !editor->action.input_active)
	{
		if (clicked_inside_ui(editor->mouse_data.x, editor->mouse_data.y,
				editor->buffer.height, editor->buffer.width))
		{
			check_ui_events(editor->mouse_data.x, editor->mouse_data.y,
				&editor->button_list, &editor->action);
			editor->mouse_data.i_mbleft = 0;
			if (editor->action.convert_to_portal == allocate && editor->temp_sector)
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
	if (editor->notify_time)
		notify_user(&editor->notification, &editor->buffer,
			editor->delta_time, &editor->notify_time);
	return (1);
}
