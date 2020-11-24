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

void	modify_pixel_add(SDL_Surface *surf, int x, int y, int color)
{
	int *pixel;
	int	red;
	int	green;
	int	blue;

	if (x > SCREEN_WIDTH - 1 || y > SCREEN_HEIGHT - 1 || x < 0 || y < 0)
		return ;
	pixel = surf->pixels + y * surf->pitch +
		x * surf->format->BytesPerPixel;
	red = (*pixel / 256 / 256 % 256) + (color / 256 / 256 % 256);
	green = (*pixel / 256 % 256) + (color / 256 % 256);
	blue = (*pixel % 256) + (color % 256);
	red = red > 255 ? 255 : red;
	green = green > 255 ? 255 : green;
	blue = blue > 255 ? 255 : blue;
	*pixel = blue + green * 256 + red * 256 * 256;
}

void	clear_surface(SDL_Surface *surface)
{
	int i;
	int	pixel_amount;

	i = 0;
	pixel_amount = SCREEN_HEIGHT * SCREEN_WIDTH;
	while (i < pixel_amount)
	{
		put_pixel(surface, i % SCREEN_WIDTH, i / SCREEN_WIDTH, 0);
		i++;
	}
}

static t_home	initialize_sdl(void)
{
	t_home		home;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
    	ft_die("Fatal: SDL Initalization failed.", &home);
    home.win.window = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, 0);
    if (home.win.window == NULL)
		ft_die("Fatal: Failed to create a window.", &home);
    //home.ren = SDL_CreateRenderer(home.win.window, -1, SDL_RENDERER_SOFTWARE);
    //if (home.ren == NULL)
	//	ft_die("Fatal: Failed to create a renderer.", &home);
	home.surf = SDL_GetWindowSurface(home.win.window);
	if (!home.surf)
		ft_die("Fatal: Failed to get window surface", &home);
	return (home);
}

void			stress_test(int max, int x, int y, t_home *home)
{
	int		i = 0;

	while (i < max)
	{
		draw_rect_center(vec2(x, y), vec2(4, 4), home);
		i++;
	}
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
		draw_grid(32, 32, &home);
		//stress_test(5000, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, &home);
		update_player(&plr, &home, e);
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
