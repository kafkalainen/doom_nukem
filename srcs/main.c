/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:13:54 by tmaarela          #+#    #+#             */
/*   Updated: 2021/10/09 13:12:50 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"

int	free_all(t_frame *frame, t_audio *audio, Uint32 *buffer,
		t_home *home)
{
	free_queues(frame);
	free(frame->buffer.pxl_buffer);
	free(buffer);
	free(home->map);
	free(home->sector_buffer);
	cleanup_audio_source(audio);
	ft_putendl("User closed the window");
	Mix_CloseAudio();
	SDL_Quit();
	return (EXIT_SUCCESS);
}

void	handle_map_and_settings(t_menu *menu, t_home *home, SDL_Event *e)
{
	if (home->game_state == MAP_MENU)
	{
		load_map_names(&menu->map_names, &menu->nbr_of_maps);
		if (menu->nbr_of_maps > 0)
			launch_load_menu_loop(menu, home, e);
		else
			home->game_state = MAIN_MENU;
	}
	if (home->game_state == MAIN_SETTINGS)
		launch_settings_menu(menu, home, e);
}

void	update_main_loop(t_buffer *buffer,
	int *game_state, SDL_Event *e, int *option)
{
	process_inputs_main_menu(game_state, e, option);
	update_main_menu(buffer, option);
}

void	set_solo_mode(char *path, char **mapname, int *game_state)
{
	if (!path)
		error_output("path is null\n");
	*mapname = ft_strdup(path);
	*game_state = GAME_LOOP;
}

int	main(int argc, char **argv)
{
	t_home		home;
	t_player	plr;
	t_frame		frame;
	t_menu		menu;
	SDL_Event	e;

	setup(&home, &plr, &frame, &menu);
	if (argc == 2)
		set_solo_mode(argv[1], &home.map, &home.game_state);
	while (home.game_state != QUIT)
	{
		update_main_loop(&menu.buffer, &home.game_state, &e, &menu.option);
		if (home.game_state == MAP_MENU || home.game_state == MAIN_SETTINGS)
			handle_map_and_settings(&menu, &home, &e);
		if (home.game_state == GAME_LOOP || home.game_state == GAME_CONTINUE)
		{
			setup_game_loop(&home, &plr, &menu.option);
			launch_game_loop(&home, &plr, &frame, &e);
		}
		if (home.game_state == EDITOR)
			launch_editor(&home, &e);
		render_buffer(menu.buffer.pxl_buffer, home.win.screen);
		SDL_UpdateWindowSurface(home.win.window);
	}
	return (free_all(&frame, &plr.audio, menu.buffer.pxl_buffer, &home));
}
