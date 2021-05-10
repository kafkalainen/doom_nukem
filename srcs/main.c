/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:13:54 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/10 11:14:52 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"

/*
** if (create_map_file(&home) < 0)
**	 	ft_putendl_fd("File creation failed\n", 2);
*/

void	exit_game(t_home *home, Uint32 *buffer, t_audio *audio)
{
	int i;

	// free_sectors(home);
	free(buffer);
	cleanup_audio(audio);
	// i = -1;
	// while (++i <= home->nbr_of_textures)
	// 	free_texture(home->editor_tex[i]);
	// free(home->editor_tex);
	free(home->t.frame_times);
	ft_putendl("User closed the window");
	SDL_Quit();
}

void	return_to_main_from_game(t_home *home, t_player *plr, t_frame *frame)
{
	int i;

	free_sectors(home);
	i = -1;
	while (++i < (home->nbr_of_textures + 1))
		free_texture(home->editor_tex[i]);
	free(home->editor_tex);
	init_player(plr);
}

void	launch_game(t_home *home, t_player *plr, t_frame *frame, SDL_Event *e)
{
	while (home->game_state == GAME_LOOP)
	{
		fps_timer(&home->t);
		update_player(plr, home, e);
		update_screen(home, frame, plr);
		render_buffer(frame->buffer, home->win.ScreenSurface);
		SDL_UpdateWindowSurface(home->win.window);
	}
	return_to_main_from_game(home, plr, frame);
}

void	process_inputs(int *game_state, SDL_Event *e, int *quit)
{
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type = SDL_KEYDOWN)
		{
			if (*game_state == MAIN_MENU && (e->key.keysym.sym == K_ESC || e->type == SDL_QUIT))
			{
				printf("calling exit\n");
				*quit = 1;
			}
			if (e->key.keysym.sym == SDLK_2)
			{
				printf("siirrytaaan game looppiin\n");
				*game_state = GAME_LOOP;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_home		home;
	t_player	plr;
	t_frame		frame;
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
		setup(argv[1], &home, &plr, &frame);
		// setup_editor(&home, &plr, &frame);
		// create_map_file(&home);
		while (plr.input.quit != 1)
		{
			process_inputs(&home.game_state, &e, &plr.input.quit);
			// setup main_menu graphics
			if (home.game_state == GAME_LOOP)
			{
				printf("kutsu setup_game_looppia\n");
				setup_game_loop(argv[1], &home, &plr, &frame);
				launch_game(&home, &plr, &frame, &e);
			}
		}
	}
	else
		error_output("fuck off\n"); // TODO: Launch main menu
	exit_game(&home, frame.buffer, &plr.audio);
	return (EXIT_SUCCESS);
}
