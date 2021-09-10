/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_modules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:04:51 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/09 23:25:16 by rzukale          ###   ########.fr       */
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
	update_entities(home, plr, delta_time);
	update_projectiles(home, plr, delta_time);
	update_lifts(home, plr, current_time, delta_time);
	update_doors(home->sectors, home->nbr_of_sectors, plr->time, delta_time);
}

void	launch_game_loop(t_home *home, t_player *plr,
	t_frame *frame, SDL_Event *e)
{
	while (home->game_state == GAME_LOOP)
	{
		fps_timer(&home->t);
		process_inputs_game_loop(plr, &home->game_state, e);
		update_world(plr, home);
		update_screen(home, frame, plr);
		render_buffer(frame->buffer.pxl_buffer, home->win.ScreenSurface);
		SDL_UpdateWindowSurface(home->win.window);
	}
	free_game_assets(home);
	SDL_SetRelativeMouseMode(SDL_FALSE);
}

static void	free_map_names(int *nbr_of_maps, int *option, char **map_names)
{
	int	i;

	i = 0;
	while (i < *nbr_of_maps)
	{
		free(map_names[i]);
		map_names[i] = NULL;
		i++;
	}
	free(map_names);
	map_names = NULL;
	*nbr_of_maps = 0;
	*option = 0;
}

void	launch_load_menu_loop(t_menu *menu, t_home *home, SDL_Event *e)
{
	menu->option = 0;
	menu->selected = 0;
	menu->start = 0;
	if ((menu->nbr_of_maps - 8) > 0)
		menu->end = 7;
	else
		menu->end = menu->nbr_of_maps - 1;
	while (home->game_state == MAP_MENU && !menu->selected)
	{
		process_inputs_load_menu(&home->game_state, e, menu);
		update_load_menu(menu, e->key.keysym.sym);
		render_buffer(menu->buffer.pxl_buffer, home->win.ScreenSurface);
		SDL_UpdateWindowSurface(home->win.window);
	}
	if (menu->selected)
		home->map = ft_strjoin("map_files/", menu->map_names[menu->option]);
	free_map_names(&menu->nbr_of_maps, &menu->option, menu->map_names);
}
