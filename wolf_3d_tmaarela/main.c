/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 18:03:24 by tmaarela          #+#    #+#             */
/*   Updated: 2020/10/14 18:11:13 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_die(const char *error_message)
{
	ft_putstr("Error: ");
	ft_putendl(error_message);
	exit(0);
}

void			init_map(char *mapname, t_map *map)
{
	char	*line;
	int		i;
	size_t	shortest;
	int		fd;
	char	buf[2];

	if ((fd = open(mapname, O_RDONLY | O_NOFOLLOW)) < 0)
		ft_die("Failed to load the map");
	if (read(fd, buf, 1) < 0)
		ft_die("Error loading the map file.");
	close(fd);
	fd = open(mapname, O_RDONLY | O_NOFOLLOW);
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

void			init_player(t_me *me, t_map *map)
{
	int y;
	int x;

	me->height = 0.5;
	me->dir = vec2(0, -0.5);
	y = 0;
	while (y < map->size.y)
	{
		x = 0;
		while (x < map->size.x)
		{
			if (map->data[y][x] == 'P')
			{
				me->pos.x = x + 0.5;
				me->pos.y = y + 0.5;
				return ;
			}
			++x;
		}
		++y;
	}
	ft_die("Player not found in the map.");
}

void			setup(char *mapname, t_prog *p)
{
	init_map(mapname, &p->map);
	init_player(&p->me, &p->map);
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, WIN_WIDTH, WIN_HEIGHT, "jes");
	p->image = ft_new_image(p->mlx, WIN_WIDTH, WIN_HEIGHT);
	p->skybox = ft_new_xpm_image(p->mlx, "px-skybox.xpm");
	p->floor = ft_new_xpm_image(p->mlx, "px-floor.xpm");
	p->wall[0] = ft_new_xpm_image(p->mlx, "img/wall1.XPM");
	p->wall[1] = ft_new_xpm_image(p->mlx, "img/wall2.XPM");
	p->wall[2] = ft_new_xpm_image(p->mlx, "img/wall3.XPM");
	p->wall[3] = ft_new_xpm_image(p->mlx, "img/wall4.XPM");
	p->key = (t_kboard){0};
	p->mouse = (t_mouse){{0, 0}, {0, 0}};
}

int				main(int argc, char **argv)
{
	t_prog p;

	if (argc != 2)
		ft_die("usage: ./wolf3d [mapname]");
	setup(argv[1], &p);
	mlx_hook(p.win, E_KEY_PRESS, E_KEY_PRESS, keyboard_press, &p.key);
	mlx_hook(p.win, E_KEY_RELEASE, E_KEY_RELEASE, keyboard_release, &p.key);
	mlx_hook(p.win, E_MOUSE_MOVE, 0, mouse_move, &p);
	mlx_hook(p.win, E_CLOSE_WIN, 0, window_close, &p);
	mlx_loop_hook(p.mlx, movement, &p);
	render(&p);
	p.time = clock();
	mlx_loop(p.mlx);
}
