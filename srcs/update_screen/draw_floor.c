/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:49:21 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/18 10:37:49 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

static void		ft_draw_tex_pixel(SDL_Surface *tex, t_screen_xy pixel,
	t_screen_xy coord, SDL_Surface *draw_surf)
{
	Uint32		color;

	SDL_LockSurface(tex);
	color = get_pixel(tex, pixel.y, pixel.x);
	SDL_UnlockSurface(tex);
	put_pixel(draw_surf, coord.x, coord.y, color);
}

static t_step	*ft_steplen(t_step *ground, int current_y, t_ray_floor hor,
	t_player *plr)
{
	double	row_dist;

	row_dist = (0.5 * SCREEN_HEIGHT) / (current_y - SCREEN_HEIGHT * 0.5);
	ground->step_len.x = row_dist * (hor.right.x - hor.left.x) / SCREEN_WIDTH;
	ground->step_len.y = row_dist * (hor.right.y - hor.left.y) / SCREEN_WIDTH;
	ground->cur_step.x = plr->pos.x + row_dist * hor.left.x;
	ground->cur_step.y = plr->pos.y + row_dist * hor.left.y;
	return (ground);
}

static void		draw_world_floor(int y, t_player *plr, t_home *home,
	t_ray_floor hor)
{
	t_step		ground;
	t_screen_xy	coord;
	t_screen_xy	tex;


	coord.x = 0;
	coord.y = y;
	ft_steplen(&ground, y, hor, plr);
	while (coord.x < SCREEN_WIDTH)
	{
		tex.x = (int)(TEX_SIZE * (ground.cur_step.x -
			(int)ground.cur_step.x)) & (TEX_SIZE - 1);
		tex.y = (int)(TEX_SIZE * (ground.cur_step.y -
			(int)ground.cur_step.y)) & (TEX_SIZE - 1);
		ground.cur_step = vec2_add(ground.cur_step, ground.step_len);
		ft_draw_tex_pixel(home->ground, tex, coord, home->draw_surf);
		coord.x++;
	}
}

void	draw_fov_floor(t_home *home, t_player *plr)
{
	t_ray_floor		horizontal;
	int				j;

	j = 0;
	horizontal.plane = vec2_rot(plr->dir, FOV * DEG_TO_RAD);
	horizontal.left = vec2_dec(plr->dir, horizontal.plane);
	horizontal.right = vec2_add(plr->dir, horizontal.plane);
	while (j < SCREEN_HEIGHT)
	{
		draw_world_floor(j, plr, home, horizontal);
		j++;
	}
}
