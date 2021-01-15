/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:49:21 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/15 18:14:34 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

static t_xy		real_world_floor(int y, t_player *plr)
{
	t_xy	plane;
	t_xy	left;
	t_xy	right;
	t_xy	floor_step;
	t_xy	step;
	double	row_dist;

	row_dist = (y - SCREEN_HEIGHT * 0.5) / (0.5 * SCREEN_HEIGHT);
	plane = vec2_rot(plr->dir, FOV * DEG_TO_RAD);
	left = vec2_dec(plr->dir, plane);
	right = vec2_add(plr->dir, plane);
	floor_step.x = row_dist * (right.x - left.x) / SCREEN_WIDTH;
	floor_step.y = row_dist * (right.y - left.y) / SCREEN_WIDTH;
	step.x = plr->pos.x + row_dist * left.x;
	step.y = plr->pos.y + row_dist * left.y;
}

void			draw_fov_floor(t_home *home, t_player *plr, SDL_Surface *surf)
{
	t_xy	floor;
	int		j;

	j = 0;
	while (j < SCREEN_HEIGHT)
	{
		real_world_floor(j, plr);
		j++;
	}
}
