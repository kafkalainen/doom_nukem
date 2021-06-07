/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_modules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:04:51 by rzukale           #+#    #+#             */
/*   Updated: 2021/06/07 13:02:23 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	process_inputs_game_loop(t_player *plr, int *game_state, SDL_Event *e)
{
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_QUIT)
		{
			*game_state = QUIT;
			break ;
		}
		key_input(plr, e, game_state);
		mouse_handle(plr, e);
	}
}

void	update_world(t_player *plr, t_home *home)
{
	Uint32	current_time;
	Uint32	delta_time;

	current_time = SDL_GetTicks();
	delta_time = current_time - plr->time;
	if (delta_time < 1)
		return ;
	plr->time = current_time;

	update_player(plr, home, delta_time);
	// TODO: update objects
}

void	launch_game_loop(t_home *home, t_player *plr,
	t_frame *frame, SDL_Event *e)
{
	while (home->game_state == GAME_LOOP)
	{
		fps_timer(&home->t);
		process_inputs_game_loop(plr, &home->game_state, e);
		update_world(plr, home); // TODO: split into process_inputs_game_loop and update_world functions
		update_screen(home, frame, plr);
		render_buffer(frame->buffer, home->win.ScreenSurface);
		SDL_UpdateWindowSurface(home->win.window);
	}
	return_to_main_from_game(home, plr);
}

void	launch_load_menu_loop(t_menu *menu, t_window *win, SDL_Event *e,
	int *game_state)
{
	int	i;

	menu->option = 0;
	menu->selected = 0;
	menu->start = 0;
	if ((menu->nbr_of_maps - 8) > 0)
		menu->end = 7;
	else
		menu->end = menu->nbr_of_maps - 1;
	while (*game_state == MAP_MENU && !menu->selected)
	{
		process_inputs_load_menu(game_state, e, menu);
		update_load_menu(menu, e->key.keysym.sym);
		render_buffer(menu->menu_buffer, win->ScreenSurface);
		SDL_UpdateWindowSurface(win->window);
	}
	if (menu->selected)
		menu->chosen_map = ft_strjoin("map_files/",
				menu->map_names[menu->option]);
	i = 0;
	while (i < menu->nbr_of_maps)
		free(menu->map_names[i++]);
	free(menu->map_names);
	menu->nbr_of_maps = 0;
	menu->option = 0;
}
