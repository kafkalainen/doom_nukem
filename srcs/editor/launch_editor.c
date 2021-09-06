/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:47:35 by rzukale           #+#    #+#             */
/*   Updated: 2021/08/12 16:35:06 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"

static void	init_mouse_data(t_mouse_data *mouse_data)
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

static void	init_actions(t_action *action)
{
	action->offset.x = 0;
	action->offset.y = 0;
	action->grid = 1;
	action->new_sector = 0;
	action->selected_sector = -1;
	action->selected_point = -1;
	action->scalar = 10;
	action->create_sector = 0;
	action->edit_sector = 0;
	action->input_active = -1;
	action->keysym = -1;
}

static t_editor	setup_editor(t_editor *editor, t_home *home)
{
	t_button	**blist;

	editor->buffer.width = 0;
	editor->buffer.height = 0;
	editor->grid_size = 32;
	blist = (t_button **)malloc(sizeof(t_button*) * NBR_BUTTONS);
	editor->button_list = create_button_list(blist);
	SDL_SetWindowFullscreen(home->win.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_GetWindowSize(home->win.window, &editor->buffer.width, &editor->buffer.height);
	SDL_SetWindowFullscreen(home->win.window, 0);
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
	return(*editor);
}


void	launch_editor(t_home *home, SDL_Event *e)
{
	t_editor	editor;
	int			i;

	editor = setup_editor(&editor, home);
	while (home->game_state == EDITOR)
	{
		editor_events(e, home, &editor);
		draw_ui(&editor);
		draw_buttons(editor.button_list, &editor.buffer);
		render_buffer(editor.buffer.pxl_buffer, home->win.ScreenSurface);
		SDL_UpdateWindowSurface(home->win.window);
	}
	// create_new_entity(&editor.entity_list, editor.mouse_data, &editor.action);
	// create_new_entity(&editor.entity_list, editor.mouse_data, &editor.action);
	// create_new_entity(&editor.entity_list, editor.mouse_data, &editor.action);
	// create_new_entity(&editor.entity_list, editor.mouse_data, &editor.action);
	create_map_file(home, &editor);
	free(editor.buffer.pxl_buffer);
	i = -1;
	while (++i < NBR_BUTTONS)
	{
		free(editor.button_list[i]->text);
		free(editor.button_list[i]);
	}
	free_all_textures(home->editor_tex, &home->nbr_of_textures);
	SDL_SetWindowSize(home->win.window, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetWindowPosition(home->win.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	home->win.ScreenSurface = SDL_GetWindowSurface(home->win.window);
}
