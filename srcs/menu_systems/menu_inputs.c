/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 13:55:49 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/01 16:45:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	update_main_menu(t_buffer *buffer, int *option)
{
	int					i;
	t_xy				coord;
	t_plx_modifier		mod;
	const char			*arr[] = {"Editor", "Load Map", "Settings", "Quit"};
	const int			tab[] = {6, 8, 8, 4};

	i = 0;
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
