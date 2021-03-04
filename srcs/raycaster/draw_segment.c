/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:50:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/04 14:29:14 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void			draw_segment(t_frame *frame, t_texture *tex, 
							t_home *home, t_player *plr)
{
	float		step;
	float		z_step;

	ft_calc_distances(frame);
	z_step = get_distance(plr->pos, frame->left.l_pt) / 
				get_distance(plr->pos, frame->left.l_pt);
	step = (frame->wall_h_l - frame->wall_h_r) / frame->wall_len;
	while (frame->wall_x1 < frame->wall_x2)
	{
		draw_tex_line(
			vec2(frame->wall_x1, 0),
			vec2(frame->wall_x1, plr->pitch - frame->wall_h_l),
			get_tex(-3, home->editor_tex),
			frame->draw_surf
		); /*drawing ceiling*/
		draw_tex_line(
			vec2(frame->wall_x1, plr->pitch + frame->wall_h_l),
			vec2(frame->wall_x1, SCREEN_HEIGHT),
			get_tex(-3, home->editor_tex),
			frame->draw_surf
		); /*drawing a floor*/
		draw_tex_line(
			vec2(frame->wall_x1, plr->pitch - frame->wall_h_l),
			vec2(frame->wall_x1, plr->pitch + frame->wall_h_l),
			tex,
			frame->draw_surf); /*drawing a wall*/
		frame->wall_h_l = frame->wall_h_l - step;
		z_step -= frame->wall_len * z_step;
		frame->wall_x1 = frame->wall_x1 + 1.0f;
	}
	draw_text(home, ft_ftoa(frame->wall_len, 9, 1), frame, vec2(frame->wall_x2 - frame->wall_len * 0.5, 240));
}
