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

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
	*(Uint32 *)target_pixel = pixel;
}

static t_home	initialize_sdl(void)
{
	t_home		home;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
    	ft_die("Fatal: SDL Initalization failed.", home);
    home.win.window = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, 0);
    if (home.win.window == NULL)
		ft_die("Fatal: Failed to create a window.", home);
    home.ren = SDL_CreateRenderer(home.win.window, -1, SDL_RENDERER_SOFTWARE);
    if (home.ren == NULL)
		ft_die("Fatal: Failed to create a renderer.", home);
	return (home);
}

int  			main(int argc, char **argv)
{
	t_home		home;
	t_player	plr;
	SDL_Event	e;

	home = initialize_sdl();
	home.t.fps = 0;
	home.t.frames = 0;
	init_player(&plr, vec2(128, 128));
	while(1)
	{
		home.t.beginfps = clock();
		SDL_SetRenderDrawColor(home.ren, 0, 0, 0, 255);
		SDL_RenderClear(home.ren);
		draw_grid(32, 32, home);
		update_player(&plr, home, e);
		SDL_SetWindowTitle(home.win.window, ft_itoa(home.t.fps));
		SDL_RenderPresent(home.ren);
		home.t.endfps = clock();
		home.t.delta_time = home.t.endfps - home.t.beginfps;
		home.t.fps = CLOCKS_PER_SEC / home.t.delta_time;
	}
	SDL_Quit();
	return 0;
}
