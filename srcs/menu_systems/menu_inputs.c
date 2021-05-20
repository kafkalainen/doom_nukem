/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 13:55:49 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/20 12:23:59 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	update_main_menu(t_buffer *menu_buffer, int option)
{
	int					i;
	int					y;
	t_plx_modifier		mod;
	const char			*arr[] = {"Editor", "Load Map", "Help", "Quit"};

	i = 0;
	y = 0;
	mod.size = MAIN_MENU_TEXT;
	while (i < 4)
	{
		if (i == option)
			mod.colour = red;
		else
			mod.colour = white;
		str_pxl(menu_buffer, (t_xy){(SCREEN_WIDTH * 0.5) - 75,
			((SCREEN_HEIGHT * 0.5) - 45) + y}, (char *)arr[i], mod);
		y += 30;
		i++;
	}
}

void	process_inputs_main_menu(int *game_state, SDL_Event *e, int *option)
{
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_KEYDOWN)
		{
			if (e->type == SDL_QUIT)
				*game_state = QUIT;
			if (e->key.keysym.sym == SDLK_ESCAPE)
				*game_state = QUIT;
			update_option_main_menu(game_state, e->key.keysym.sym, option);
		}
	}
}

void	process_inputs_load_menu(int *game_state, SDL_Event *e, t_menu *menu)
{
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_KEYDOWN)
		{
			if (e->type == SDL_QUIT)
				*game_state = QUIT;
			if (e->key.keysym.sym == SDLK_ESCAPE)
				*game_state = MAIN_MENU;
			update_option_load_menu(game_state, menu, e->key.keysym.sym);
		}
	}
}
