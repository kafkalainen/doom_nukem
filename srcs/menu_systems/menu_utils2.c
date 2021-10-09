/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:44:14 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/09 13:13:25 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	get_color(enum e_colour color)
{
	Uint8	alpha;
	Uint8	red;
	Uint8	green;
	Uint8	blue;

	alpha = 0xFF;
	red = (color & 0xFF0000) >> 16;
	green = (color & 0x00FF00) >> 8;
	blue = (color & 0x0000FF);
	return (((alpha << 24)) | (red << 16) | (green << 8) | (blue));
}

int	get_game_state(int *option)
{
	if (*option == 0)
		return (EDITOR);
	if (*option == 1)
		return (MAP_MENU);
	if (*option == 2)
		return (MAIN_SETTINGS);
	if (*option == 3)
		return (QUIT);
	return (QUIT);
}

void	update_option_main_menu(int *game_state, int sym, int *option)
{
	if (sym == SDLK_UP)
	{
		if (*option > 0 && *option < 4)
			*option = *option - 1;
		else if (*option == 0)
			*option = 3;
	}
	if (sym == SDLK_DOWN)
	{
		if (*option >= 0 && *option < 3)
			*option = *option + 1;
		else if (*option == 3)
			*option = 0;
	}
	if (sym == SDLK_RETURN || sym == SDLK_KP_ENTER)
		*game_state = get_game_state(option);
}

void	update_option_load_menu(int *game_state, t_menu *menu, int sym)
{
	if (sym == SDLK_UP)
	{
		if (menu->option > 0 && menu->option < menu->nbr_of_maps)
			menu->option = menu->option - 1;
		else if (menu->option == 0)
			menu->option = (menu->nbr_of_maps - 1);
	}
	if (sym == SDLK_DOWN)
	{
		if (menu->option >= 0 && menu->option < (menu->nbr_of_maps - 1))
			menu->option = menu->option + 1;
		else if (menu->option == (menu->nbr_of_maps - 1))
			menu->option = 0;
	}
	if (sym == SDLK_RETURN || sym == SDLK_KP_ENTER)
	{
		*game_state = GAME_LOOP;
		menu->selected = true;
	}
}

void	free_game_assets(t_home *home, t_audio *audio)
{
	if (home->t.frame_times)
		free(home->t.frame_times);
	free_sectors(home);
	free_all_textures(home->textures, NUM_TEX);
	free_entities(home);
	free_projectiles(home);
	cleanup_audio_source(audio);
	if (home->game_state != GAME_CONTINUE
		&& home->map)
	{
		free(home->map);
		home->map = NULL;
	}
}
