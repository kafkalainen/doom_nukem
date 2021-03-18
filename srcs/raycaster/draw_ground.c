/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ground.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 14:59:22 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/18 11:25:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

// static void	assign_ground(t_step *ground, int y, t_frame *frame)
// {
// 	float		row_dist;
	
// 	row_dist = fabsf((float)(SCREEN_HEIGHT * 0.5 / (y - SCREEN_HEIGHT * 0.5)));
// 	ground->step_len.x = row_dist * frame->screen_wall_len / SCREEN_WIDTH;
// 	ground->step_len.y = row_dist * frame->screen_wall_len / SCREEN_WIDTH;
// 	ground->cur_step = vec2(frame->wall_x1, y);
// }

// void		draw_ground(t_player *plr, t_frame *frame, t_home *home)
// {
// 	float		i;
// 	float		ground_y;
// 	t_step		ground;
// 	t_screen_xy	cell;
// 	t_screen_xy	coord;
// 	t_screen_xy	tex;

// 	i = SCREEN_HEIGHT;
// 	ground_y = ft_fmin(frame->wall_h_l, frame->wall_h_r);
//  	while (i > plr->pitch + ground_y)
// 	{
// 		assign_ground(&ground, i, frame);
// 		coord.x = frame->wall_x1;
// 		coord.y = i;
// 		while (coord.x < frame->wall_x2)
// 		{
// 			cell.x = (int)ground.cur_step.x;
// 			cell.y = (int)ground.cur_step.y;
// 			tex.x = (int)(TEX_SIZE * (ground.cur_step.x - cell.x)) & (TEX_SIZE - 1);
// 			tex.y = (int)(TEX_SIZE * (ground.cur_step.y - cell.y)) & (TEX_SIZE - 1);
// 			if	(coord.x >= 0 && coord.x < SCREEN_WIDTH && 
// 				coord.y >= 0 && coord.y < SCREEN_HEIGHT)
// 				put_pixel(frame->draw_surf, coord.x, coord.y, get_texel(tex.x, tex.y, get_tex(-3, home->editor_tex)));
// 			ground.cur_step = vec2_add(ground.cur_step, ground.step_len);
// 			coord.x++;
// 		}
// 		i--;
// 	}
// }
