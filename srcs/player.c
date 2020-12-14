/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:33:56 by tmaarela          #+#    #+#             */
/*   Updated: 2020/11/20 15:33:56 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../doom_nukem.h" 

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
	ft_die_destroy("Player not found in the map.");
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
}

void	update_player(t_player *plr, t_home *home, SDL_Event e)
{
	key_input(plr, e, home);
	movement(plr);
	draw_rect_center(vec2(plr->pos.x, plr->pos.y), vec2(16, 16), home);
	ft_draw_line(vec2(plr->pos.x, plr->pos.y),
		vec2_add(vec2(plr->pos.x, plr->pos.y),
		vec2_mul(vec2(plr->dir.x, plr->dir.y), 64)), 0xFFFFFF, home->surf);
}
