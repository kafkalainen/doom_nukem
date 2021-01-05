/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycaster.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:24:37 by tmaarela          #+#    #+#             */
/*   Updated: 2020/12/22 13:24:37 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

static void		init(t_raycast *rc, t_xy pos, t_xy ray, t_xy map_pos)
{
	rc->deltaDist = (t_xy){fabs(1 / ray.x), fabs(1 / ray.y)};
	rc->step.x = (ray.x < 0) ? -1 : 1;
	rc->sideDist.x = (ray.x < 0) ?
		(pos.x - map_pos.x) * rc->deltaDist.x :
		(map_pos.x + 1 - pos.x) * rc->deltaDist.x;
	rc->step.y = (ray.y < 0) ? -1 : 1;
	rc->sideDist.y = (ray.y < 0) ?
		(pos.y - map_pos.y) * rc->deltaDist.y :
		(map_pos.y + 1 - pos.y) * rc->deltaDist.y;
}

t_wall			cast_ray(t_xy pos, t_xy ray, t_map *map)
{
	t_raycast	rc;
	int			map_x;
	int			map_y;

	map_x = (int)pos.x;
	map_y = (int)pos.y;
	init(&rc, pos, ray, vec2(map_x, map_y));
	while (((map_x >= 0 && map_x < map->size.x)
	&& (map_y >= 0 && map_y < map->size.y)) && map->data[map_y][map_x] != '#')
		if (rc.sideDist.x < rc.sideDist.y)
		{
			rc.sideDist.x += rc.deltaDist.x;
			map_x += rc.step.x;
			rc.side = VERTICAL_WALL;
		}
		else
		{
			rc.sideDist.y += rc.deltaDist.y;
			map_y += rc.step.y;
			rc.side = HORIZONTAL_WALL;
		}
	rc.perpWallDist = (rc.side == VERTICAL_WALL) ?
		(map_x - pos.x + (1 - rc.step.x) / 2) / ray.x :
		(map_y - pos.y + (1 - rc.step.y) / 2) / ray.y;
	return ((t_wall){vec2(map_x, map_y), rc.perpWallDist, rc.side});
}

t_xy			init_ray(t_xy pos, t_xy plane, t_xy left, double angle)
{
	t_xy	point;
	t_xy	ray;

	point = vec2_add(left, vec2_mul(plane, angle));
	ray = vec2_norm(vec2_dec(point, pos));
	return (ray);
}

void			draw_fov(t_home *home, t_player *plr, SDL_Surface *surf)
{
	static double	step = 2.0 / SCREEN_WIDTH;
	t_xy			plane;
	t_xy			left;
	t_xy			ray;
	int				i;

	draw_rect_center(vec2(plr->pos.x, plr->pos.y), vec2(16, 16), home);
	ft_draw_line(vec2(plr->pos.x, plr->pos.y),
	vec2_add(vec2(plr->pos.x, plr->pos.y),
	vec2_mul(vec2(plr->dir.x, plr->dir.y), 64)), 0xFFFFFF, home->surf);
	plane = vec2_rot(plr->dir, FOV * DEG_TO_RAD);
	left = vec2_dec(vec2_add(plr->pos, plr->dir), plane);
	i = 0;
	while (i < SCREEN_WIDTH)
	{
		ray = init_ray(plr->pos, plane, left, step * i);
		draw_wall(i, cast_ray(plr->pos, ray, &home->map), ray, home, surf, plr);
		++i;
	}
}
