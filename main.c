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

void			init_map(char *mapname, t_map *map)
{
	char	*line;
	int		i;
	size_t	shortest;
	int		fd;
	char	buf[2];

	if ((fd = _open(mapname, _O_RDONLY)) < 0)
		ft_die_destroy("Failed to load the map");
	if (read(fd, buf, 1) < 0)
		ft_die_destroy("Error loading the map file.");
	close(fd);
	fd = _open(mapname, _O_RDONLY);
	i = 0;
	shortest = -1;
	while (ft_get_next_line(fd, &line) && i < MAP_MAX_LINES)
	{
		if (ft_strlen(line) < shortest)
			shortest = ft_strlen(line);
		map->data[i] = ft_strdup(line);
		free(line);
		++i;
	}
	map->size.y = i;
	map->size.x = (int)shortest;
}

void			setup(char *mapname, t_home *home, t_player *plr)
{
	init_map(mapname, &home->map);
	init_player(plr, &home->map);
}

int  			main(int argc, char **argv)
{
	t_home		home;
	t_player	plr;
	SDL_Event	e;

	if (argc != 2)
		ft_die_destroy("usage: .\\play [map file name]\n");
	home = initialize_sdl();
	home.t.fps = 0;
	home.t.frames = 0;
	setup(argv[1], &home, &plr);
	while(1)
	{
		home.t.beginfps = clock();
		update_player(&plr, &home, e);
		draw_top_view(home.map.size, plr.pos, plr.dir, &home);
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
