/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:13:54 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/12 11:08:03 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"

/*
** if (create_map_file(&home) < 0)
**	 	ft_putendl_fd("File creation failed\n", 2);
*/

void	exit_game(t_home *home, Uint32 *buffer, t_audio *audio)
{
	// free_sectors(home);
	free(buffer);
	cleanup_audio(audio);
	free(home->t.frame_times);
	ft_putendl("User closed the window");
	SDL_Quit();
}

void	return_to_main_from_game(t_home *home, t_player *plr)
{
	int i;

	free_sectors(home);
	i = -1;
	while (++i < (home->nbr_of_textures + 1))
		free_texture(home->editor_tex[i]);
	free(home->editor_tex);
	init_player(plr);
}

int	main(int argc, char **argv)
{
	t_home		home;
	t_player	plr;
	t_frame		frame;
	t_menu		menu;
	SDL_Event	e;

	// TODO: master setup that initializes SDL functions and mallocs buffers etc.
	// launch main_menu loop
	// boolean statement on which branch to launch, editor or game
	// editor state: init all assets from sources, on exit free all assets and go back to main_menu loop
	// game state: request map file, init assets from file and launch game loop. on exit free assets and return to main_menu loop
	// on exit from main_menu loop: free assets initialized during master setup and call exit
	if (argc > 2)
		error_output("usage: ./doom-nukem");
	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		setup(&home, &plr, &frame);
		// setup_editor(&home);
		// create_map_file(&home);
		menu.nbr_of_maps = 0;
		while (home.game_state != QUIT)
		{
			process_inputs_main_menu(&home.game_state, &e);
			// setup main_menu graphics
			if (home.game_state == EDITOR)
			{
				printf("olen editorissa\n");
				//load_editor();
			}
			if (home.game_state == MAP_MENU)
			{
				printf("olen map menussa\n");
				load_map_names(&menu);
				if (menu.nbr_of_maps > 0)
					launch_load_menu_loop(&menu, &frame.buffer, &e, &home.game_state);
			}
			if (home.game_state == GAME_LOOP)
			{
				printf("olen game loopissa\n");
				setup_game_loop(&menu.chosen_map, &home, &plr);
				launch_game_loop(&home, &plr, &frame, &e);
			}
			render_buffer(frame.buffer, home.win.ScreenSurface);
			SDL_UpdateWindowSurface(home.win.window);
		}
	}
	else
		error_output("fuck off\n"); // TODO: Launch main menu
	exit_game(&home, frame.buffer, &plr.audio);
	return (EXIT_SUCCESS);
}
