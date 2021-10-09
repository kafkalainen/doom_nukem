/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:47:35 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/09 07:22:30 by jnivala          ###   ########.fr       */
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
	SDL_SetRelativeMouseMode(SDL_FALSE);
}

void	reset_actions(t_action *action)
{
	action->selected_sector = -1;
	action->selected_entity = -1;
	action->selected_wall = -1;
	action->prev_entity = -1;
	action->draw_depth = 0;
	action->delete = false;
}

static void	setup_editor(t_editor *editor, t_home *home)
{
	initialize_editor_values(editor);
	editor->button_list = (t_button **)malloc(sizeof(t_button *) * NBR_BUTTONS);
	if (!editor->button_list)
		error_output("ERROR: Memory allocation of button list failed!");
	editor->button_list = create_button_list(editor->button_list);
	add_notification(editor, "Hello, welcome to doom-nukem editor", 3000);
	SDL_SetWindowSize(home->win.window,
		editor->buffer.width, editor->buffer.height);
	SDL_SetWindowPosition(home->win.window,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	editor->buffer.pxl_buffer = (Uint32 *)malloc(sizeof(Uint32)
			* (Uint32)editor->buffer.width * (Uint32)editor->buffer.height);
	if (!editor->buffer.pxl_buffer)
		error_output("ERROR: Memory for drawing bufferallocation failed!");
	home->win.screen = SDL_GetWindowSurface(home->win.window);
	init_textures(home);
	init_mouse_data(&editor->mouse_data);
	initialize_actions(&editor->action, &editor->buffer);
	load_map_names_to_memory(editor);
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

	setup_editor(&editor, home);
	while (home->game_state == EDITOR)
	{
		editor_events(e, home, &editor);
		handle_events(&editor, home);
		draw_ui(&editor, home->textures);
		draw_buttons(&editor, home->textures);
		render_buffer(editor.buffer.pxl_buffer, home->win.screen);
		SDL_UpdateWindowSurface(home->win.window);
	}
	free_editor_data(&editor);
	free_all_textures(home->textures, NUM_TEX);
	SDL_SetWindowSize(home->win.window, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetWindowPosition(home->win.window,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	home->win.screen = SDL_GetWindowSurface(home->win.window);
}
