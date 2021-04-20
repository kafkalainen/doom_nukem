/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 13:49:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/18 15:06:33 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"
void		debug_wall(t_home *home, t_frame *frame)
{
	if (frame->left.wall->c == 'b')
	{
		// draw_text(home, "LEFT", frame, vec2(frame->wall_x1, 220));
		// draw_text(home, ft_ftoa(frame->wall_x1, 2, 1), frame,
		// 	vec2(frame->wall_x1, 240));
		// draw_text(home, "LEFT_PT: X and Y", frame, vec2(20, 260));
		// draw_text(home, ft_ftoa(frame->left.l_pt.x, 2, 1), frame,
		// 	vec2(frame->wall_x1, 280));
		// draw_text(home, ft_ftoa(frame->left.l_pt.y, 2, 1), frame,
		// 	vec2(frame->wall_x1, 300));
		// draw_text(home, "FULL_LEN_LEFT_PT: X and Y", frame, vec2(20, 320));
		// draw_text(home, ft_ftoa(frame->left.wall->x0.x, 2, 1), frame,
		// 	vec2(frame->wall_x1, 340));
		// draw_text(home, ft_ftoa(frame->left.wall->x0.y, 2, 1), frame,
		// 	vec2(frame->wall_x1, 360));
		// draw_text(home, "RIGHT", frame, vec2(frame->wall_x2 * 0.75, 220));
		// draw_text(home, ft_ftoa(frame->wall_x2, 2, 1), frame,
		// 	vec2(frame->wall_x2, 240));
		// draw_text(home, "RIGHT_PT: X and Y", frame,
		// 	vec2(frame->wall_x2 * 0.75, 260));
		// draw_text(home, ft_ftoa(frame->left.r_pt.x, 2, 1), frame,
		// 	vec2(frame->wall_x2, 280));
		// draw_text(home, ft_ftoa(frame->left.r_pt.y, 2, 1), frame,
		// 	vec2(frame->wall_x2, 300));
		// draw_text(home, "FULL_LEN_RIGHT_PT: X and Y", frame,
		// 	vec2(frame->wall_x2, 320));
		// draw_text(home, ft_ftoa(frame->left.wall->next->x0.x, 2, 1), frame,
		// 	vec2(frame->wall_x2, 340));
		// draw_text(home, ft_ftoa(frame->left.wall->next->x0.y, 2, 1), frame,
		// 	vec2(frame->wall_x2, 360));
		// draw_text(home, "WALL_LEN", frame, vec2(frame->wall_x2 * 0.5, 200));
		// draw_text(home, ft_ftoa(frame->screen_wall_len, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 220));
		// draw_text(home, "FULL_WALL_DIST", frame,
		// 	vec2(frame->wall_x2 * 0.5, 240));
		// draw_text(home, ft_ftoa(frame->full_wall_dist, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 260));
		// draw_text(home, "VISIBLE_WALL_DIST", frame, vec2(frame->wall_x2 * 0.5, 280));
		// draw_text(home, ft_ftoa(frame->visible_wall_dist, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 300));
		// draw_text(home, "RATIO", frame, vec2(frame->wall_x2 * 0.5, 320));
		// draw_text(home, ft_ftoa(frame->ratio, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 340));
		// draw_text(home, "UNVISIBLE LEFTSIDE", frame, vec2(frame->wall_x2 * 0.5, 360));
		// draw_text(home, ft_ftoa(frame->unvisible_l_side, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 380));
		// draw_text(home, "INVZ", frame, vec2(frame->wall_x2 * 0.5, 400));
		// draw_text(home, ft_ftoa(frame->top_left.z, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 420));
		// draw_text(home, "WALL_FRACT_LEN", frame, vec2(frame->wall_x2 * 0.5, 400));
		// draw_text(home, ft_ftoa(frame->wall_fract_len, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 420));
		draw_text(home, "TOP_LEFT_UV: X", frame,
			vec2(frame->top_left.x, 20));
		draw_text(home, ft_ftoa(frame->uv_top_left.x, 4, 1), frame,
			vec2(frame->top_left.x, 40));
		draw_text(home, "TOP_LEFT_UV: Y", frame,
			vec2(frame->top_left.x, 60));
		draw_text(home, ft_ftoa(frame->uv_top_left.y, 4, 1), frame,
			vec2(frame->top_left.x, 80));
		draw_text(home, "TOP_LEFT_UV: Z", frame,
			vec2(frame->top_left.x, 100));
		draw_text(home, ft_ftoa(frame->uv_top_left.z, 4, 1), frame,
			vec2(frame->top_left.x, 120));
		draw_text(home, "BOTTOM_LEFT_UV: X", frame,
			vec2(frame->top_left.x, 400));
		draw_text(home, ft_ftoa(frame->uv_bottom_left.x, 4, 1), frame,
			vec2(frame->top_left.x, 420));
		draw_text(home, "BOTTOM_LEFT_UV: Y", frame,
			vec2(frame->top_left.x, 440));
		draw_text(home, ft_ftoa(frame->uv_bottom_left.y, 4, 1), frame,
			vec2(frame->top_left.x, 460));
		draw_text(home, "TOP_RIGHT_UV: X", frame,
			vec2(frame->top_right.x, 20));
		draw_text(home, ft_ftoa(frame->uv_top_right.x, 4, 1), frame,
			vec2(frame->top_right.x, 40));
		draw_text(home, "TOP_RIGHT_UV: Y", frame,
			vec2(frame->top_right.x, 60));
		draw_text(home, ft_ftoa(frame->uv_top_right.y, 4, 1), frame,
			vec2(frame->top_right.x, 80));
		draw_text(home, "TOP_RIGHT_UV: Z", frame,
			vec2(frame->top_right.x, 100));
		draw_text(home, ft_ftoa(frame->uv_top_right.z, 4, 1), frame,
			vec2(frame->top_right.x, 120));
		draw_text(home, "BOTTOM_RIGHT_UV: X", frame,
			vec2(frame->top_right.x, 400));
		draw_text(home, ft_ftoa(frame->uv_bottom_right.x, 4, 1), frame,
			vec2(frame->top_right.x, 420));
		draw_text(home, "BOTTOM_RIGHT_UV: Y", frame,
			vec2(frame->top_right.x, 440));
		draw_text(home, ft_ftoa(frame->uv_bottom_right.y, 4, 1), frame,
			vec2(frame->top_right.x, 460));
	}
}
