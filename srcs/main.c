/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:13:54 by tmaarela          #+#    #+#             */
/*   Updated: 2021/04/22 16:45:24 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"

/*
** if (create_map_file(&home) < 0)
**	 	ft_putendl_fd("File creation failed\n", 2);
*/

int	main(int argc, char **argv)
{
	t_home		home;
	t_player	plr;
	t_frame		frame;
	SDL_Event	e;

	if (argc != 2)
		error_output("usage: ./doom-nukem [path to mapfile]");
	setup(argv[1], &home, &plr, &frame);
	if (open_file(&home, "map_files/test.DATA") < 0)
		error_output("Could not successfully open map file.");
	while (!plr.input.quit)
	{
		fps_timer(&home.t);
		update_player(&plr, &home, &e);
		update_screen(&home, &frame, &plr);
		render_buffer(frame.buffer, home.win.ScreenSurface);
		SDL_UpdateWindowSurface(home.win.window);
		clear_surface(frame.buffer);
	}
	free_sectors(&home);
	free(frame.buffer);
	cleanup_audio(&plr.audio);
	ft_putendl("User closed the window");
	SDL_Quit();
	return (EXIT_SUCCESS);
}
