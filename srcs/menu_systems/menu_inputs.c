/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 13:55:49 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/08 14:51:12 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	write_title(t_buffer *buffer, t_plx_modifier *mod)
{
	t_xy	coord;

	mod->colour = get_color(yellow);
	mod->size = MAIN_TITLE_LARGE;
	ft_c_pxl(buffer, vec2(222, SCREEN_HEIGHT * 0.25f - 9), 'd', *mod);
	ft_c_pxl(buffer, vec2(550, SCREEN_HEIGHT * 0.25f - 9), 'm', *mod);
	coord = vec2(0, SCREEN_HEIGHT * 0.25f);
	mod->len = 8;
	mod->size = MAIN_TITLE_SMALL;
	coord.x = center_text_x_axis(0, SCREEN_WIDTH, mod->size, mod->len);
	ft_str_pxl(buffer, coord, "oom nuke", *mod);
}

void	update_main_menu(t_buffer *buffer, int *option)
{
	int					i;
	t_xy				coord;
	t_plx_modifier		mod;
	const char			*arr[] = {"Editor", "Load Map", "Settings", "Quit"};
	const int			tab[] = {6, 8, 8, 4};

	i = 0;
	write_title(buffer, &mod);
	coord = vec2(0, SCREEN_HEIGHT * 0.5f - 45);
	mod.size = MAIN_MENU_TEXT;
	while (i < 4)
	{
		if (i == *option)
			mod.colour = 0xFFFFCC00;
		else
			mod.colour = 0xFFFFFFFF;
		mod.len = tab[i];
		coord.x = center_text_x_axis(0, SCREEN_WIDTH, mod.size, mod.len);
		ft_str_pxl(buffer, coord, (char *)arr[i], mod);
		coord.y += 30;
		i++;
	}
}

void	process_inputs_main_menu(int *game_state, SDL_Event *e, int *option)
{
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_QUIT)
			*game_state = QUIT;
		if (e->type == SDL_KEYDOWN)
		{
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
		if (e->type == SDL_QUIT)
			*game_state = QUIT;
		if (e->type == SDL_KEYDOWN)
		{
			if (e->key.keysym.sym == SDLK_ESCAPE)
				*game_state = MAIN_MENU;
			update_option_load_menu(game_state, menu, e->key.keysym.sym);
		}
	}
}
