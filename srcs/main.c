/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:13:54 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/08 18:26:57 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"

int	free_all(t_frame *frame, t_audio *audio, Uint32 *buffer,
		char **chosen_map)
{
	free_queues(frame);
	free(frame->buffer.pxl_buffer);
	free(buffer);
	ft_strdel(chosen_map);
	cleanup_audio_source(audio);
	ft_putendl("User closed the window");
	SDL_Quit();
	return (EXIT_SUCCESS);
}

void	handle_map_menu(t_menu *menu, t_home *home, SDL_Event *e)
{
	load_map_names(&menu->map_names, &menu->nbr_of_maps);
	if (menu->nbr_of_maps > 0)
		launch_load_menu_loop(menu, home, e);
	else
		home->game_state = MAIN_MENU;
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
		if (home.game_state == MAP_MENU)
			handle_map_menu(&menu, &home, &e);
		if (home.game_state == GAME_LOOP || home.game_state == GAME_CONTINUE)
		{
			setup_game_loop(&home, &plr, &menu.option);
			launch_game_loop(&home, &plr, &frame, &e);
		}
		if (home.game_state == EDITOR)
			launch_editor(&home, &e);
		render_buffer(menu.buffer.pxl_buffer, home.win.ScreenSurface);
		SDL_UpdateWindowSurface(home.win.window);
	}
	return (free_all(&frame, &plr.audio, menu.buffer.pxl_buffer, &home.map));
}
