/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:49:21 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/16 11:15:26 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

#include "../../doom_nukem.h"

static void ft_draw_tex_pixel(SDL_Surface *tex, t_screen_xy pixel, \
	t_screen_xy coord, SDL_Surface *draw_surf)
{
	Uint32		color;

	SDL_LockSurface(tex);
	color = get_pixel(tex, (int)pixel.y, (int)pixel.x);
	SDL_UnlockSurface(tex);
	put_pixel(draw_surf, coord.x, coord.y, color);
}

static t_xy real_world_floor(int y, t_player *plr, t_home *home)
{
	t_xy		plane;
	t_xy		left;
	t_xy		right;
	t_xy		floor_step;
	t_xy		step;
	t_screen_xy	cell;
	t_screen_xy	tex;
	double		row_dist;
	t_screen_xy	coord;

	coord.x = 0;
	coord.y = y;
	row_dist = (0.5 * SCREEN_HEIGHT) / (y - SCREEN_HEIGHT * 0.5);
	plane = vec2_rot(plr->dir, FOV * DEG_TO_RAD);
	left = vec2_dec(plr->dir, plane);
	right = vec2_add(plr->dir, plane);
	floor_step.x = row_dist * (right.x - left.x) / SCREEN_WIDTH;
	floor_step.y = row_dist * (right.y - left.y) / SCREEN_WIDTH;
	step.x = plr->pos.x + row_dist * left.x;
	step.y = plr->pos.y + row_dist * left.y;
	while (coord.x < SCREEN_WIDTH)
	{
		cell.x = (int)step.x;
		cell.y = (int)step.y;
		tex.x = (int)(TEX_SIZE * (step.x - cell.x)) & (TEX_SIZE - 1);
		tex.y = (int)(TEX_SIZE * (step.y - cell.y)) & (TEX_SIZE - 1);
		step = vec2_add(step, floor_step);
		ft_draw_tex_pixel(home->ground, tex, coord, home->draw_surf);
		coord.x++;
	}
}

void	draw_fov_floor(t_home *home, t_player *plr)
{
	t_xy	floor;
	int		j;

	j = 0;
	while (j < SCREEN_HEIGHT)
	{
		real_world_floor(j, plr, home);
		j++;
	}
}
