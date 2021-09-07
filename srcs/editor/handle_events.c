#include "../headers/doom_nukem.h"

// void	check_event(t_mouse_data *mouse_data, t_button **list, t_action *action)
// {
// 	int	i;

// 	i = 0;
// 	while(i < NBR_BUTTONS)
// 	{
// 		if (check_bbox(list[i]->ltop, list[i]->wh, mouse_data->x, mouse_data->y) == 1)
// 			button_actions(action, i);
// 		i++;
// 	}
// 	i = 0;
// }

void	new_check_event(t_editor *editor)
{
	// int	i;
	// t_button	**list;
	t_mouse_data	mdata;

	// list = editor->button_list;
	mdata = editor->mouse_data;
	// i = 0;
	// if (mdata.x > 0 && mdata.x < 300 && mdata.y > 0 && mdata.y < editor->buffer.height)
	// {
	// 	printf("we are clickin in the UI part\n");
	// 	while(i < NBR_BUTTONS)
	// 	{
	// 		if (list[i]->info.draw_depth == editor->action.draw_depth)
	// 		{
	// 			if (check_bbox(list[i]->ltop, list[i]->wh, mdata.x, mdata.y) == 1)
	// 				button_actions(&editor->action, i);
	// 		}
	// 		i++;
	// 	}

	// }
	if (mdata.x > 300 && mdata.x < editor->buffer.width && mdata.y > 0 && mdata.y < editor->buffer.height)
	{
		
	}
	if (editor->action.link_entity == 2 && editor->action.prev_entity != -1 && editor->temp_entity != NULL)
	{
		link_entities(&editor->entity_list, mdata, editor->action.prev_entity);
		editor->action.link_entity = 0;
	}
}

void	reset_actions(t_action *action)
{
	action->selected_sector = -1;
	action->selected_point = -1;
	action->create_sector = 0;
	action->edit_sector = 0;
	action->input_active = -1;
	action->keysym = -1;
	action->move = 0;
}

unsigned char	*delete_char_from_string(unsigned char **string)
{
	unsigned char	*temp;
	int				size;

	size = ft_strlen((const char *)*string);
	if (size > 0)
	{
		temp =  (unsigned char *)ft_strnew(sizeof(char) * (size - 1));
		temp = (unsigned char *)ft_strncpy((char *)temp, (const char *)*string, (size - 1));
		free(*string);
	}
	else
		return (NULL);
	return (temp);
}

void	read_input_string(unsigned char **string, t_action *action)
{
	char 	c;

	if (action->keysym == SDLK_BACKSPACE && *string != NULL)
		*string = delete_char_from_string(string);
	if (ft_isspace(action->keysym) ||
		(*string != NULL && (ft_strlen((const char *)*string) > MAX_FILE_NAME_LENGHT && action->save_file)))
	{
		action->keysym = -1;
		return ;
	}
	else if (action->input_active && ft_isprint(action->keysym))
	{
		if (*string == NULL)
		{
			*string = (unsigned char *)ft_strnew(sizeof(char) * 1);
			*string = (unsigned char *)ft_strncat((char *)*string, (const char *)&c, 1);
		}
		else
			*string = (unsigned char *)ft_strjoin_freeable((char *)*string, (char *)&c, 1, 0);
	}
	action->keysym = -1;
}

void	unlink_selected_entity(t_entity_list **list, int entity_idx, int *unlink_state)
{
	t_entity_list	*temp;

	temp = *list;
	while (temp != NULL && temp->entity_idx != entity_idx)
		temp = temp->next;
	if (temp != NULL)
		temp->is_linked = 0;
	*unlink_state = 0;
}

void	check_ui_events(int x, int y, t_button ***blist, t_action *action)
{
	t_button	**list;
	int			i;

	i = 0;
	list = *blist;
	while (i < NBR_BUTTONS)
	{
		if (list[i]->info.draw_depth == action->draw_depth)
		{
			if (check_bbox(list[i]->ltop, list[i]->wh, x, y))
			{
				if (list[i]->info.draw_depth == depth_zero)
					main_button_actions(action, i);
				else if (list[i]->info.draw_depth == entity)
					entity_button_actions(action, i);
				// else if (list[i]->info.draw_depth == wall)
				// 	wall_button_actions(action, i);
				// button_actions(action, i);
				break ;
			}
		}
		i++;
	}
}

int		clicked_inside_grid(int x, int y, int height, int width)
{
	if (x > 300 && x < width && y > 0 && y < height)
		return (TRUE);
	return (FALSE);
}

int		clicked_inside_ui(int x, int y, int height, int width)
{
	if (x > 0 && x < 300 && x < width && y > 0 && y < height)
		return (TRUE);
	return (FALSE);
}

int		check_plr_start_and_end_sector_exists(t_sector_list **list, t_plr_pos plr, int end_sector)
{
	t_sector_list	*temp;
	t_sector_list	*temp_two;

	temp = *list;
	temp_two = *list;
	while (temp != NULL && temp->idx_sector != plr.sector)
		temp = temp->next;
	if (temp == NULL)
		return (FALSE);
	if (!check_bbox(temp->bbox.start, temp->bbox.end, plr.x, plr.z))
		return (FALSE);
	while (temp_two != NULL && temp_two->idx_sector != end_sector)
		temp_two = temp_two->next;
	if (temp_two == NULL)
		return (FALSE);
	return (TRUE);
}

int		check_saving_prerequisites(t_editor *editor)
{
	if (editor->mapname == NULL || !editor->action.player_start_assigned || !editor->end_sector)
		return (FALSE);
	if (!check_plr_start_and_end_sector_exists(&editor->sector_list, editor->plr, editor->end_sector))
		return (FALSE);
	printf("Saving map into file\n");
	return (TRUE);
}

void	save_editor_map(t_editor *editor, t_home *home)
{
	if (editor->mapname == NULL || editor->action.input_active || !editor->action.map_name_set)
		read_input_string(&editor->mapname, &editor->action);
	if (editor->action.input_active == -1 || editor->action.map_name_set)
	{
		if (!editor->action.map_name_set && editor->mapname != NULL)
		{
			editor->mapname = (unsigned char *)ft_strjoin_freeable((char *)editor->mapname, ".DN", 1, 0);
			editor->mapname = (unsigned char *)ft_strjoin_freeable("./map_files/", (char *)editor->mapname, 0, 1);
			editor->action.map_name_set = 1;
		}		
		if (check_saving_prerequisites(editor))
			create_map_file(home, editor);
		editor->action.save_file = 0;
		editor->action.input_active = -1;
	}
}

void	assign_end_sector(t_sector_list **list, t_screen_xy *mdata, int *end_sector, int *sector_assigned)
{
	t_sector_list	*temp;

	temp = *list;
	while (temp != NULL && !check_bbox(temp->bbox.start, temp->bbox.end, mdata->x, mdata->y))
		temp = temp->next;
	if (temp == NULL)
		return ;
	*end_sector = temp->idx_sector;
	*sector_assigned = 0;
}

int		assign_player_start(t_sector_list **list, t_screen_xy *mdata, t_plr_pos *plr, int *assign_player_start)
{
	t_sector_list	*temp;

	temp = *list;
	while (temp != NULL && !check_bbox(temp->bbox.start, temp->bbox.end, mdata->x, mdata->y))
		temp = temp->next;
	if (temp == NULL)
		return (FALSE);
	plr->sector = temp->idx_sector;
	plr->x = mdata->x;
	plr->z = mdata->y;
	*assign_player_start = 0;
	return (TRUE);
}

t_sector_list	*get_clicked_sector(t_sector_list **list, t_screen_xy mdata, int *selected_sector)
{
	t_sector_list	*temp;

	temp = *list;
	while (temp != NULL)
	{
		if (check_bbox(temp->bbox.start, temp->bbox.end, mdata.x, mdata.y))
		{
			*selected_sector = temp->idx_sector;
			return (temp);
		}
		temp = temp->next;
	}
	*selected_sector = -1;
	return (NULL);
}

t_editor_walls	*get_clicked_wall(t_editor_walls **walls, t_screen_xy mdata, int *selected_wall, int nbr_of_walls)
{
	t_editor_walls	*temp;
	int				i;

	i = 0;
	temp = *walls;
	while (temp != NULL && i < nbr_of_walls)
	{
		if (check_bbox(temp->bbox.start, temp->bbox.end, mdata.x, mdata.y))
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

void	check_grid_events(t_editor *editor)
{
	t_screen_xy	mdata;

	mdata.x = (editor->mouse_data.x - editor->action.offset.x) / editor->action.scalar;
	mdata.y = (editor->mouse_data.y - editor->action.offset.y) / editor->action.scalar;
	editor->temp_sector = get_clicked_sector(&editor->sector_list, mdata, &editor->action.selected_sector);
	if (editor->temp_sector) // we know we hit a sector
	{
		editor->action.draw_depth = sector;
		editor->action.prev_entity = editor->action.selected_entity;
		editor->temp_entity = get_clicked_entity(&editor->entity_list, mdata, &editor->action.selected_entity);
		editor->temp_wall = get_clicked_wall(&editor->temp_sector->walls, mdata, &editor->action.selected_wall, editor->temp_sector->nb_of_walls);
		if (editor->temp_entity)
			editor->action.draw_depth = entity;
		else if (editor->temp_wall)
			editor->action.draw_depth = wall;
	}
	else
		editor->action.draw_depth = depth_zero;
	if (editor->action.delete && (editor->action.selected_entity >= 0 || editor->action.selected_sector >= 0))
	{
		if (editor->action.selected_entity >= 0)
			delete_entity(&editor->entity_list, &editor->action);
	}
	if (editor->action.edit_entity)
		edit_entity(editor->temp_entity, &editor->action);
	if (editor->action.assign_player_start == 2)
		editor->action.player_start_assigned = assign_player_start(&editor->sector_list, &mdata, &editor->plr, &editor->action.assign_player_start);
	if (editor->action.assign_end_sector == 2)
		assign_end_sector(&editor->sector_list, &mdata, &editor->end_sector, &editor->action.assign_end_sector);
}

void	link_maps(t_action *action, unsigned char **linked_mapname, char **map_names)
{
	*linked_mapname = (unsigned char *)ft_strjoin("./map_files/", map_names[action->option]);
	action->link_maps = 0;
	action->option = 0;
	action->start = 0;
}

int		handle_events(t_editor *editor, t_home *home)
{
	// check mouse click
	// if UI side, check button bboxes
	// if GRID side, if selected sector >= 0
	// check if clicked entity bbox
	// otherwise if selected_sector == -1
	// check for sector bbox
	(void)home;
	// if (editor->action.save_file)
	// {
	// 	printf("taalla\n");
	// 	if (editor->mapname == NULL || editor->action.input_active)
	// 		write_map_name(editor->mapname, &editor->action);
	// 	// else if (editor->mapname && editor->action.input_active == -1)
	// 		// check for correct data and correct if necessary
	// 		// then write out the file
	// }
	if (editor->action.unlink_entity)
		unlink_selected_entity(&editor->entity_list, editor->action.selected_entity, &editor->action.unlink_entity);
	if (editor->action.create_sector)
	{
		create_new_sector(&editor->sector_list, &editor->action);
		editor->action.create_sector = 0;
		editor->action.edit_sector = 1;
	}
	if (editor->action.input_active && editor->action.edit_sector)
	{
		//handle_sector(&editor->sector_list, &editor->mouse_data, &editor->action);
		if (handle_sector(&editor->sector_list, &editor->mouse_data, &editor->action))
			editor_free_selected_sector(editor, editor->action.selected_sector);
	}
	if (editor->action.create_entity == 2)
	{
		// if mouse click within selected sectors bounding box
		// allow to create entity
		create_new_entity(&editor->entity_list, &editor->mouse_data, &editor->action, editor->temp_sector);
		editor->action.create_entity = 0;
	}
	if (editor->mouse_data.i_mbleft)
	{
		if (clicked_inside_ui(editor->mouse_data.x, editor->mouse_data.y, editor->buffer.height, editor->buffer.width))
		{
			check_ui_events(editor->mouse_data.x, editor->mouse_data.y, &editor->button_list, &editor->action);
			editor->mouse_data.i_mbleft = 0;
		}
		else if (clicked_inside_grid(editor->mouse_data.x, editor->mouse_data.y, editor->buffer.height, editor->buffer.width))
			check_grid_events(editor);
		// editor->mouse_data.i_mbleft = 0;
	}
	// if (editor->mouse_data.i_mbleft)
	// 	new_check_event(editor);
	if (editor->action.save_file)
		save_editor_map(editor, home);
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
