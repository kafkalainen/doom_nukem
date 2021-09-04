/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:13:54 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/04 13:21:27 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"

/*
** if (create_map_file(&home) < 0)
**	 	ft_putendl_fd("File creation failed\n", 2);
*/

void	free_main_assets(t_frame *frame, t_audio *audio, Uint32 *menu_buffer,
		char **chosen_map)
{
	free_queues(frame);
	free(frame->buffer);
	free(menu_buffer);
	ft_strdel(chosen_map);
	cleanup_audio_source(audio);
	ft_putendl("User closed the window");
	SDL_Quit();
}

void	handle_map_menu(t_menu *menu, t_home *home, SDL_Event *e)
{
	load_map_names(menu);
	if (menu->nbr_of_maps > 0)
		launch_load_menu_loop(menu, home, e);
	else
		home->game_state = MAIN_MENU;
}

int	main(void)
{
	t_home		home;
	t_player	plr;
	t_frame		frame;
	t_menu		menu;
	SDL_Event	e;

	setup(&home, &plr, &frame, &menu);
	while (home.game_state != QUIT)
	{
		process_inputs_main_menu(&home.game_state, &e, &menu.option);
		update_main_menu(menu.menu_buffer, menu.option);
		if (home.game_state == MAP_MENU)
			handle_map_menu(&menu, &home, &e);
		if (home.game_state == GAME_LOOP || home.game_state == GAME_CONTINUE)
		{
			setup_game_loop(&home, &plr, &menu.option);
			launch_game_loop(&home, &plr, &frame, &e);
		}
		if (home.game_state == EDITOR)
			launch_editor(&home, &e);
		render_buffer(menu.menu_buffer, home.win.ScreenSurface);
		SDL_UpdateWindowSurface(home.win.window);
	}
	free_main_assets(&frame, &plr.audio, menu.menu_buffer, &home.chosen_map);
	return (EXIT_SUCCESS);
}
