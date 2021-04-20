/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/04/20 17:24:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void			draw_2d(t_home *home, t_frame *frame, t_player *plr)
{
	static t_xy	prev_pos;

	frame->idx = plr->current_sector;
	frame->old_idx = -1;
	frame->max_fov = 0;
	frame->offset = 640;
	frame->left.l_pt = vec2(-1,-1);
	frame->right.r_pt = vec2(-1,-1);
	frame->plr_offset = vec2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	frame->pxl_offset = 0.0f;
	scan_fov(home, frame, plr, 0);
	draw_text(home, "x:", frame, (t_xy){10.0f, 10.0f});
	draw_text(home, ft_ftoa(plr->pos.x, 7, 1), frame, (t_xy){10.0f, 30.0f});
	draw_text(home, "y:", frame, (t_xy){10.0f, 50.0f});
	draw_text(home, ft_ftoa(plr->pos.y, 7, 1), frame, (t_xy){10.0f, 70.0f});
	draw_text(home, "dir:", frame, (t_xy){10.0f, 90.0f});
	draw_text(home, ft_ftoa(plr->dir.x, 7, 1), frame, (t_xy){10.0f, 110.0f});
}
