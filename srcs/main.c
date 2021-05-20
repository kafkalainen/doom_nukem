/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:13:54 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/20 11:50:01 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"

/*
** if (create_map_file(&home) < 0)
**	 	ft_putendl_fd("File creation failed\n", 2);
*/

void	exit_game(t_home *home, Uint32 *buffer, t_audio *audio, Uint32 *menu_buffer)
{
	// free_sectors(home);
	free(buffer);
	free(menu_buffer);
	cleanup_audio(audio);
	free(home->t.frame_times);
	ft_putendl("User closed the window");
	SDL_Quit();
}

int	main(int argc, char **argv)
{
	t_home		home;
	t_player	plr;
	t_frame		frame;
	t_menu		menu;
	SDL_Event	e;

	argc = argc;
	argv = argv;
	setup(&home, &plr, &frame, &menu);
	while (home.game_state != QUIT)
	{
		process_inputs_main_menu(&home.game_state, &e, &menu.option);
		update_main_menu(menu.menu_screen.buffer, menu.option);
		if (home.game_state == MAP_MENU)
		{
			load_map_names(&menu);
			if (menu.nbr_of_maps > 0)
				launch_load_menu_loop(&menu, &home.win, &e, &home.game_state);
			else
				home.game_state = MAIN_MENU;
		}
		if (home.game_state == GAME_LOOP)
		{
			setup_game_loop(&menu.chosen_map, &home, &plr, &menu.option);
			launch_game_loop(&home, &plr, &frame, &e);
		}
		if (home.game_state == EDITOR)
			launch_editor(&home, &e);
		render_buffer(menu.menu_screen.buffer, home.win.ScreenSurface);
		SDL_UpdateWindowSurface(home.win.window);
	}
	exit_game(&home, frame.buffer, &plr.audio, menu.menu_screen.buffer);
	return (EXIT_SUCCESS);
}
