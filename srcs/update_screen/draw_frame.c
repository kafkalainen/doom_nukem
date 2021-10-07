/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/10/07 14:26:56 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static Uint32	blueshift_color(int take_damage)
{
	int	rev_value;

	rev_value = 255 - take_damage;
	if (rev_value > 220)
		return (255 << 24 | rev_value << 16 | rev_value << 8 | 255);
	return (255 << 24 | rev_value << 16 | 220 << 8 | 255);
}

static void	fill_with_red(t_buffer *buffer, int take_damage)
{
	t_pxl_coords	x0;
	Uint32			color;

	x0.x = 0;
	color = blueshift_color(take_damage);
	while (x0.x < buffer->width)
	{
		x0.y = 0;
		while (x0.y < buffer->height)
		{
			put_pixel(buffer, x0, color);
			x0.y++;
		}
		x0.x++;
	}
}

static void	draw_and_manage_fade_in(t_frame *frame, int plr_is_dead)
{
	if (plr_is_dead)
	{
		frame->buffer.lightness -= 0.05f;
		if (frame->buffer.lightness < 0.0f)
			frame->buffer.lightness = 0.0f;
	}
	else
	{
		frame->buffer.lightness += 0.012f;
		if (frame->buffer.lightness > 1.0f)
			frame->buffer.lightness = 1.0f;
	}
}

void	draw_frame(t_home *home, t_frame *frame, t_player *plr)
{
	if (plr->plot_state == start_cutscene)
		draw_cutscene(&frame->buffer, plr, home->sectors[plr->start_sector]);
	else if (plr->plot_state == end_cutscene)
		draw_cutscene(&frame->buffer, plr, home->sectors[home->end_sector]);
	else
	{
		frame->idx = plr->cur_sector;
		reset_depth_buffer(frame->depth_buffer);
		draw_game(home, frame, plr);
		if (plr->input.info)
			draw_info(frame, plr, (int)home->t.fps);
		if (plr->take_damage)
			fill_with_red(&frame->buffer, plr->take_damage);
		draw_heads_up_display(home, frame, plr);
		draw_plot_state(home, &frame->buffer, plr);
		draw_object_data(&frame->buffer, plr);
		if (frame->buffer.lightness < 0.99f || plr->dead)
			draw_and_manage_fade_in(frame, plr->dead);
	}
	return ;
}
