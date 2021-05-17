/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:44:14 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/17 11:45:27 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	get_game_state(int *option)
{
	if (*option == 0)
		return (EDITOR);
	if (*option == 1)
		return (MAP_MENU);
	if (*option == 2)
		return (MAIN_MENU);
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
	if (sym == SDLK_RETURN ||sym == SDLK_KP_ENTER)
	{
		*game_state = GAME_LOOP;
		menu->selected = TRUE;
	}
}
