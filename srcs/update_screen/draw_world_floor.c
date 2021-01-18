/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world_floor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:45:28 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/18 11:54:36 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void		draw_world_floor(int y, t_player *plr, t_home *home,
	t_ray_floor hor)
{
	t_step		ground;
	t_screen_xy	cell;
	t_screen_xy	coord;
	t_screen_xy	tex;

	coord.x = 0;
	coord.y = y;
	steplen(&ground, y, hor, plr);
	while (coord.x < SCREEN_WIDTH)
	{
		cell.x = (int)ground.cur_step.x;
		cell.y = (int)ground.cur_step.y;
		tex.x = (int)(TEX_SIZE * (ground.cur_step.x - cell.x)) & (TEX_SIZE - 1);
		tex.y = (int)(TEX_SIZE * (ground.cur_step.y - cell.y)) & (TEX_SIZE - 1);
		draw_tex_pixel(home->ground, tex, coord, home->draw_surf);
		ground.cur_step = vec2_add(ground.cur_step, ground.step_len);
		coord.x++;
	}
}
