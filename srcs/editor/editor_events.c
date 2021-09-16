/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparviai <eparviai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:31:05 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/15 18:32:33 by eparviai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	editor_events(SDL_Event *e, t_home *home, t_editor *editor)
{
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_KEYDOWN)
			editor_keyboard(e->key.keysym.sym, &editor->action);
		editor_mouse(&editor->mouse_data, e, &editor->action, &editor->buffer);
		if (e->type == SDL_QUIT)
			home->game_state = QUIT;
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
			home->game_state = MAIN_MENU;
	}
}
