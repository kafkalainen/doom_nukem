/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:13:54 by tmaarela          #+#    #+#             */
/*   Updated: 2021/04/20 16:03:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"

int  			main(int argc, char **argv)
{
	t_home		home;
	t_player	plr;
	t_frame		frame;
	SDL_Event	e;
	char		*fps;

	if (argc > 1)
	 	error_output("usage: .\\play [map file name]\n");
	//new_sector("sector00 4 5 10 -3 -4 40,200,1 250,200,2 200,0,1 90,0,-10 -5\n");
	setup(argv[1], &home, &plr, &frame);
	update_sector(&home);
	// if (create_map_file(&home) < 0)
	//  	printf("File creation failed\n");
	if (open_file(&home, "map_files/test.DATA") < 0)
	 	printf("Could not successfully open map file\n");
	transform_world_view(&home, -45 * DEG_TO_RAD);
	while (1)
	{
		home.t.beginfps = clock();
		update_player(&plr, &home, &e);
		update_screen(&home, &frame, &plr);
		fps = ft_itoa(home.t.fps);
		SDL_SetWindowTitle(home.win.window, fps);
		free(fps);
		SDL_UpdateWindowSurface(home.win.window);
		clear_surface(frame.draw_surf);
		SDL_FreeSurface(frame.draw_surf);
		//home.t.endfps = clock();
		//home.t.delta_time = home.t.endfps - home.t.beginfps;
		//home.t.fps = CLOCKS_PER_SEC / home.t.delta_time;
	}
	TTF_Quit();
	SDL_Quit();
	return 0;
}
