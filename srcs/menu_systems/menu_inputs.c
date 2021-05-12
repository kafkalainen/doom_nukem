/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 13:55:49 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/12 11:55:25 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	process_inputs_main_menu(int *game_state, SDL_Event *e)
{
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_KEYDOWN)
		{
			if (e->type == SDL_QUIT)
				*game_state = QUIT;
			if (*game_state == MAIN_MENU && e->key.keysym.sym == SDLK_ESCAPE)
			{
				printf("game state is main menu, calling exit\n");
				*game_state = QUIT;
			}
			if (*game_state != MAIN_MENU && *game_state != QUIT && e->key.keysym.sym == SDLK_ESCAPE)
			{
				printf("going back to main menu\n");
				*game_state = MAIN_MENU;
			}
			if (e->key.keysym.sym == SDLK_2 && *game_state == MAIN_MENU)
				*game_state = MAP_MENU;
			if (e->key.keysym.sym == SDLK_3)
				*game_state = GAME_LOOP;
			if (e->key.keysym.sym == SDLK_1 && *game_state == MAIN_MENU)
				*game_state = EDITOR;
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
			{
				printf("game state is load menu, calling main menu\n");
				*game_state = MAIN_MENU;
			}
			if (e->key.keysym.sym == SDLK_UP)
			{
				if (menu->option > 0 && menu->option < menu->nbr_of_maps)
					menu->option = menu->option - 1;
				else if (menu->option == 0)
					menu->option = (menu->nbr_of_maps - 1);
				printf("option %i : map_name: %s\n", menu->option, menu->map_names[menu->option]);
			}
			if (e->key.keysym.sym == SDLK_DOWN)
			{
				if (menu->option >= 0 && menu->option < (menu->nbr_of_maps - 1))
					menu->option = menu->option + 1;
				else if (menu->option == (menu->nbr_of_maps - 1))
					menu->option = 0;
				printf("option %i : map_name: %s\n", menu->option, menu->map_names[menu->option]);
			}
			if (e->key.keysym.sym == SDLK_RETURN || e->key.keysym.sym == SDLK_KP_ENTER)
			{
				*game_state = GAME_LOOP;
				menu->selected = TRUE;
			}
			
		}
	}
}
