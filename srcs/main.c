/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:13:54 by tmaarela          #+#    #+#             */
/*   Updated: 2021/04/21 12:52:57 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"

int	main(int argc, char **argv)
{
	t_home		home;
	t_player	plr;
	t_frame		frame;
	SDL_Event	e;

	if (argc != 2)
	 	error_output("usage: .\\play [map file name]\n");
	setup(argv[1], &home, &plr, &frame);
	if (open_file(&home, "map_files/test.DATA") < 0)
	 	error_output("Could not successfully open map file\n");
	// if (create_map_file(&home) < 0)
	// 	ft_putendl_fd("File creation failed\n", 2);
	while (!plr.input.quit)
	{
		update_player(&plr, &home, &e);
		update_screen(&home, &frame, &plr);
		SDL_UpdateWindowSurface(home.win.window);
		clear_surface(frame.draw_surf);
		SDL_FreeSurface(frame.draw_surf);
	}
	free_sectors(&home);
	cleanup_audio(&plr.audio);
	ft_putendl("User closed the window");
	SDL_Quit();
	return (EXIT_SUCCESS);
}
