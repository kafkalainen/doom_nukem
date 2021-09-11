/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:47:35 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/11 14:22:24 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	init_mouse_data(t_mouse_data *mouse_data)
{
	mouse_data->i_mbleft = 0;
	mouse_data->i_mbright = 0;
	mouse_data->selected = -1;
	mouse_data->x = 0;
	mouse_data->y = 0;
	mouse_data->x_rel = 0;
	mouse_data->y_rel = 0;
	SDL_SetRelativeMouseMode(SDL_FALSE);
}

void	reset_actions(t_action *action)
{
	action->selected_sector = -1;
	action->selected_point = -1;
	action->selected_entity = -1;
	action->selected_wall = -1;
	action->prev_entity = -1;
	action->draw_depth = 0;
	action->delete = 0;
}

void	init_actions(t_action *action)
{
	action->offsetf = vec2(0.0f, 0.0f);
	action->grid = 1;
	action->selected_sector = -1;
	action->selected_point = -1;
	action->selected_entity = -1;
	action->selected_wall = -1;
	action->scalarf = 0.125f;
	action->create_sector = idle;
	action->create_entity = idle;
	action->link_entity = 0;
	action->prev_entity = -1;
	action->edit_sector = idle;
	action->input_active = 0;
	action->keysym = -1;
	action-> move = 0;
	action->link_maps = 0;
	action->unlink_maps = 0;
	action->open_file = 0;
	action->save_file = 0;
	action->draw_depth = 0;
	action->delete = 0;
	action->edit_entity = 0;
	action->change_entity_type = 0;
	action->toggle_entity_is_linked = 0;
	action->toggle_is_static = 0;
	action->toggle_is_revealed = 0;
	action->create_elevator = 0;
	action->create_light_button = 0;
	action->create_elev_button = 0;
	action->create_powerstation = 0;
	action->map_name_set = 0;
	action->player_start_assigned = 0;
	action->assign_end_sector = 0;
	action->assign_player_start = 0;
	action->unlink_entity = 0;
	action->edit_wall = 0;
	action->edit_floor_height = 0;
	action->edit_ceiling_height = 0;
	action->convert_to_portal = 0;
	action->change_wall_texture = 0;
	action->change_floor_texture = 0;
	action->change_ceiling_texture = 0;
	action->set_light_intensity = 0;
	action->create_light_source = 0;
	action->add_wall_point = 0;
	action->write_sector_story = 0;
}

static t_editor	setup_editor(t_editor *editor, t_home *home)
{
	editor->buffer.width = 0;
	editor->buffer.height = 0;
	editor->grid_size = 32;
	editor->button_list = (t_button **)malloc(sizeof(t_button*) * NBR_BUTTONS);
	editor->button_list = create_button_list(editor->button_list);
	editor->buffer.width = 1200;
	editor->buffer.height = 900;
	editor->cur_time = SDL_GetTicks();
	editor->notification = NULL;
	add_notification(&editor->notification, "Hello user, welcome to editor",
		&editor->notify_time, 3000);
	// SDL_SetWindowFullscreen(home->win.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	// SDL_GetWindowSize(home->win.window, &editor->buffer.width, &editor->buffer.height);
	// SDL_SetWindowFullscreen(home->win.window, 0);
	SDL_SetWindowSize(home->win.window, editor->buffer.width, editor->buffer.height);
	SDL_SetWindowPosition(home->win.window, 0, 0);
	if (!(editor->buffer.pxl_buffer = (Uint32*)malloc(sizeof(Uint32) *
		(Uint32)editor->buffer.width * (Uint32)editor->buffer.height)))
		error_output("Memory allocation failed!\n");
	home->win.ScreenSurface = SDL_GetWindowSurface(home->win.window);
	init_textures(home);
	init_mouse_data(&editor->mouse_data);
	init_actions(&editor->action);
	editor->sector_list = NULL;
	editor->entity_list = NULL;
	editor->linked_mapname = NULL;
	editor->mapname = NULL;
	editor->temp_entity = NULL;
	editor->temp_sector = NULL;
	editor->temp_wall = NULL;
	editor->map_names = NULL;
	editor->int_string = NULL;
	editor->end_sector = -1;
	editor->plr.x = 0;
	editor->plr.z = 0;
	editor->plr.sector = 0;
	load_map_names_to_memory(editor);
	return(*editor);
}

void	free_all_entities(t_entity_list **head)
{
	t_entity_list	*temp;

	while (*head != NULL)
	{
		temp = *head;
		*head = temp->next;
		free(temp);
		temp = NULL;
	}
}

void	launch_editor(t_home *home, SDL_Event *e)
{
	t_editor	editor;
	int			i;

	editor = setup_editor(&editor, home);
	while (home->game_state == EDITOR)
	{
		editor_events(e, home, &editor);
		handle_events(&editor, home);
		draw_ui(&editor, home->textures);
		draw_buttons(&editor, editor.end_sector, home->textures);
		render_buffer(editor.buffer.pxl_buffer, home->win.ScreenSurface);
		SDL_UpdateWindowSurface(home->win.window);
	}
	free(editor.buffer.pxl_buffer);
	i = -1;
	while (++i < NBR_BUTTONS)
	{
		free(editor.button_list[i]->info.text);
		free(editor.button_list[i]);
	}
	i = 0;
	while (i < editor.action.nbr_of_maps)
		free(editor.map_names[i++]);
	if (editor.map_names)
		free(editor.map_names);
	if (editor.mapname)
		free(editor.mapname);
	if (editor.linked_mapname)
		free(editor.linked_mapname);
	if (editor.int_string)
		free(editor.int_string);
	editor.temp_entity = NULL;
	editor.temp_sector = NULL;
	editor.temp_wall = NULL;
	free(editor.button_list);
	free_all_entities(&editor.entity_list);
	editor_free_all_sectors(&editor.sector_list);
	free_all_textures(home->textures, NUM_TEX);
	SDL_SetWindowSize(home->win.window, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetWindowPosition(home->win.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	home->win.ScreenSurface = SDL_GetWindowSurface(home->win.window);
}
