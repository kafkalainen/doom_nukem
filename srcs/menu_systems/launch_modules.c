/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_modules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:04:51 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/09 08:29:33 by jnivala          ###   ########.fr       */
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
		if (plr->plot_state != start_cutscene
			|| plr->plot_state != end_cutscene)
			mouse_handle(plr, e);
	}
}

void	update_world(t_player *plr, t_home *home, Uint32 delta_time)
{
	update_player(plr, home, delta_time);
	update_entities(home, plr, delta_time);
	update_projectiles(home, plr, delta_time);
	update_lifts(home, plr, delta_time);
	update_doors(home->sectors, plr, home->nbr_of_sectors, delta_time);
}

void	launch_game_loop(t_home *home, t_player *plr,
	t_frame *frame, SDL_Event *e)
{
	Uint32	delta_time;

	while (home->game_state == GAME_LOOP)
	{
		fps_timer(&home->t);
		delta_time = home->t.frame_time_last - plr->time;
		if (delta_time > 60)
			delta_time = 60;
		plr->time = home->t.frame_time_last;
		if (plr->plot_state == start_cutscene
			|| plr->plot_state == end_cutscene)
			update_cutscene(plr, home, delta_time);
		else
			update_world(plr, home, delta_time);
		process_inputs_game_loop(plr, &home->game_state, e);
		update_screen(home, frame, plr);
		render_buffer(frame->buffer.pxl_buffer, home->win.screen);
		SDL_UpdateWindowSurface(home->win.window);
	}
	free_game_assets(home, &plr->audio);
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
		render_buffer(menu->buffer.pxl_buffer, home->win.screen);
		SDL_UpdateWindowSurface(home->win.window);
	}
	if (menu->selected)
		home->map = ft_strjoin("map_files/", menu->map_names[menu->option]);
	free_map_names(&menu->nbr_of_maps, &menu->option, menu->map_names);
}
