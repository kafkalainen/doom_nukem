/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_settings_menu.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:16:51 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/30 16:01:09 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	update_settings_menu(t_buffer *buffer, int *option)
{
	int					i;
	int					y;
	t_plx_modifier		mod;
	const char			*arr[] = {"Easy", "Medium", "Hard", "Return"};

	i = 0;
	y = 0;
	mod.size = MAIN_MENU_TEXT;
	mod.len = 8;
	while (i < 4)
	{
		if (i == *option)
			mod.colour = get_color(red);
		else
			mod.colour = get_color(white);
		ft_str_pxl(buffer, vec2((SCREEN_WIDTH * 0.5) - 75,
				((SCREEN_HEIGHT * 0.5) - 45) + y), (char *)arr[i], mod);
		y += 30;
		i++;
	}
}

void	update_option_settings_menu(int *game_state, int sym,
	int *option, int *selected)
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
	{
		*game_state = MAIN_MENU;
		*selected = TRUE;
	}
}

void	process_inputs_settings_menu(int *game_state, SDL_Event *e,
	int *option, int *selected)
{
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_KEYDOWN)
		{
			if (e->type == SDL_QUIT)
				*game_state = QUIT;
			if (e->key.keysym.sym == SDLK_ESCAPE)
				*game_state = MAIN_MENU;
			update_option_settings_menu(game_state, e->key.keysym.sym,
				option, selected);
		}
	}
}

static int	get_option(float difficulty)
{
	if (difficulty == EASY)
		return (0);
	if (difficulty == NORMAL)
		return (1);
	if (difficulty == HARD)
		return (2);
	return (1);
}

void	launch_settings_menu(t_menu *menu, t_home *home, SDL_Event *e)
{
	int	selected;
	int	option;

	option = get_option(home->difficulty);
	selected = 0;
	while (home->game_state == MAIN_SETTINGS && selected == 0)
	{
		process_inputs_settings_menu(&home->game_state, e, &option, &selected);
		update_settings_menu(&menu->buffer, &option);
		render_buffer(menu->buffer.pxl_buffer, home->win.screen);
		SDL_UpdateWindowSurface(home->win.window);
	}
	if (selected)
	{
		if (option == 0)
			home->difficulty = EASY;
		else if (option == 1)
			home->difficulty = NORMAL;
		else if (option == 2)
			home->difficulty = HARD;
	}
}
