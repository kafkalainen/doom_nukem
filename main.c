/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:13:54 by tmaarela          #+#    #+#             */
/*   Updated: 2020/11/05 19:14:06 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*		Do you still need this shit?
void			stress_test(int max, int x, int y, t_home *home)
{
	int		i = 0;

	while (i < max)
	{
		draw_rect_center(vec2(x, y), vec2(4, 4), home);
		i++;
	}
}
*/


int  			main(int argc, char **argv)
{
	t_home		home;
	t_player	plr;
	SDL_Event	e;

	if (argc != 2)
		error_output("usage: .\\play [map file name]\n");
	setup(argv[1], &home, &plr);
	while(1)
	{
		home.t.beginfps = clock();
		update_player(&plr, &home, e, home.surf);
		update_screen(&home, &plr);
		SDL_SetWindowTitle(home.win.window, ft_itoa(home.t.fps));
		SDL_UpdateWindowSurface(home.win.window);
		clear_surface(home.surf);
		home.t.endfps = clock();
		home.t.delta_time = home.t.endfps - home.t.beginfps;
		home.t.fps = CLOCKS_PER_SEC / home.t.delta_time;
	}
	SDL_Quit();
	return 0;
}
