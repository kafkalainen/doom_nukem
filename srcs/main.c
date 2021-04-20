/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:13:54 by tmaarela          #+#    #+#             */
/*   Updated: 2021/04/20 18:59:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"

int  			main(int argc, char **argv)
{
	t_home		home;
	t_player	plr;
	t_frame		frame;
	SDL_Event	e;

	if (argc != 2)
	 	error_output("usage: .\\play [map file name]\n");
	setup(argv[1], &home, &plr, &frame);
	// if (create_map_file(&home) < 0)
	//  	printf("File creation failed\n");
	if (open_file(&home, "map_files/test.DATA") < 0)
	 	printf("Could not successfully open map file\n");
	transform_world_view(&home, -45 * DEG_TO_RAD);
	while (1)
	{
		update_player(&plr, &home, &e);
		update_screen(&home, &frame, &plr);
		SDL_UpdateWindowSurface(home.win.window);
		clear_surface(frame.draw_surf);
		SDL_FreeSurface(frame.draw_surf);
	}
	SDL_Quit();
	return 0;
}
