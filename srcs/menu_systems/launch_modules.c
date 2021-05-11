/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_modules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:04:51 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/11 15:24:01 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	launch_game_loop(t_home *home, t_player *plr, t_frame *frame, SDL_Event *e)
{
	while (home->game_state == GAME_LOOP && home->game_state)
	{
		fps_timer(&home->t);
		update_player(plr, home, e);
		update_screen(home, frame, plr);
		render_buffer(frame->buffer, home->win.ScreenSurface);
		SDL_UpdateWindowSurface(home->win.window);
	}
	return_to_main_from_game(home, plr);
}

void	launch_load_menu_loop(t_home *home, Uint32 **buffer, SDL_Event *e)
{
	int option;
	int	selected;

	selected = 0;
	option = 0;
	while (home->game_state == MAP_MENU && !selected)
	{
		process_inputs_load_menu(&home->game_state, e, &option, home->nbr_of_maps, &selected);
	}
	if (selected)
		printf("you chose %s\n", home->map_names[option]);

}
