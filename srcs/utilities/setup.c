#include "../../doom_nukem.h"

static t_home	*init_sdl(t_home *home)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
    	error_output_sdl("Fatal: SDL Initalization failed.", &home);
    home->win.window = SDL_CreateWindow("Hello World!", 100, 100, home->win.width, home->win.height, 0);
    if (home->win.window == NULL)
		error_output_sdl("Fatal: Failed to create a window.", &home);
	SDL_SetWindowPosition(home->win.window,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	home->draw_surf = SDL_GetWindowSurface(home->win.window);
	if (!home->draw_surf)
		error_output_sdl("Fatal: Failed to get window surface", &home);
	return (home);
}

void			init_map(char *mapname, t_map *map)
{
	char	*line;
	int		i;
	size_t	shortest;
	int		fd;
	char	buf[2];

	if ((fd = OPEN_FILE(mapname, READ_ONLY)) < 0)
		error_output("Failed to load the map");
	if (read(fd, buf, 1) < 0)
		error_output("Error loading the map file.");
	close(fd);
	fd = OPEN_FILE(mapname, READ_ONLY);
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

static void		set_player_position(t_player *plr, t_map *map)
{
	int x;
	int y;

	y = 0;
	while (y < map->size.y)
	{
		x = 0;
		while (x < map->size.x)
		{
			if (map->data[y][x] == 'P')
			{
				plr->pos.x = x + 0.5;
				plr->pos.y = y + 0.5;
				return ;
			}
			++x;
		}
		++y;
	}
	error_output("Player not found in the map.");
}

void	init_player(t_player *plr, t_map *map)
{
	printf("Y: %f, X: %f\n", map->size.y, map->size.x);
	for (int i = 0; i < map->size.y; i++) {
		printf("%s\n", map->data[i]);
	}
	set_player_position(plr, map);
	plr->z = 0;
	plr->dir.x = 1;
	plr->dir.y = 0;
	plr->input.down = 0;
	plr->input.up = 0;
	plr->input.right = 0;
	plr->input.left = 0;
	plr->time = 0;
	plr->height = 0.5;
}

void			setup(char *mapname, t_home *home, t_player *plr)
{
	home->win.width = 640;
	home->win.height = 480;
	home->t.fps = 0;
	home->t.frames = 0;
	home = init_sdl(home);
	home->wall[0] = SDL_LoadBMP("wall1.bmp");
	home->wall[1] = SDL_LoadBMP("wall1.bmp");
	home->wall[2] = SDL_LoadBMP("wall1.bmp");
	home->wall[3] = SDL_LoadBMP("wall1.bmp");
	init_map(mapname, &home->map);
	init_player(plr, &home->map);
}
