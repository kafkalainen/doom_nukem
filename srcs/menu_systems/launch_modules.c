/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_modules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:04:51 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/14 11:41:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	return_to_main_from_game(t_home *home, t_player *plr)
{
	int i;

	free_sectors(home);
	i = -1;
	while (++i < (home->nbr_of_textures + 1))
		free_texture(home->editor_tex[i]);
	free(home->editor_tex);
	init_player(plr);
}

void	launch_game_loop(t_home *home, t_player *plr, t_frame *frame, SDL_Event *e)
{
	while (home->game_state == GAME_LOOP)
	{
		fps_timer(&home->t);
		update_player(plr, home, e);
		update_screen(home, frame, plr);
		render_buffer(frame->buffer, home->win.ScreenSurface);
		SDL_UpdateWindowSurface(home->win.window);
	}
	return_to_main_from_game(home, plr);
}

void	update_load_menu(t_menu *menu, int sym)
{
	int y;
	int i;
	t_plx_modifier	mod;

	if (sym == SDLK_DOWN)
	{
		if (menu->option == 0)
		{
			menu->start = 0;
			if ((menu->nbr_of_maps - 8) > 0)
				menu->end = 7;
			else
				menu->end = menu->nbr_of_maps - 1;
		}
		if (menu->option > menu->end)
			menu->end = menu->option;
		if ((menu->end - 7) > 0)
			menu->start = (menu->end - 7);
		else
			menu->start = 0;
	}
	else if (sym == SDLK_UP)
	{
		if (menu->option == menu->nbr_of_maps - 1)
		{
			menu->end = menu->option;
			if ((menu->option - 7) > 0)
				menu->start = (menu->option - 7);
			else
				menu->start = 0;
		}
		if (menu->option < menu->start)
			menu->start = menu->option;
		if ((menu->start + 7) > menu->nbr_of_maps - 1)
			menu->end = menu->nbr_of_maps - 1;
		else
			menu->end = (menu->start + 7);
	}
	i = menu->start;
	y = 0;
	mod.colour = 0;
	mod.size = TEXT_SIZE;
	while (i <= menu->end)
	{
		if (i == menu->option)
			mod.colour = red;
		else
			mod.colour = white;
		str_pxl(menu->menu_buffer, (t_xy){(SCREEN_WIDTH * 0.5) - 200, 25 + y}, menu->map_names[i], mod);
		y += 15;
		i++;
	}

}

void	launch_load_menu_loop(t_menu *menu, t_window *win, SDL_Event *e, int *game_state)
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
		menu->chosen_map = ft_strjoin("map_files/", menu->map_names[menu->option]);
	i = 0;
	while (i < menu->nbr_of_maps)
		free(menu->map_names[i++]);
	free(menu->map_names);
	menu->nbr_of_maps = 0;
	menu->option = 0;
}
