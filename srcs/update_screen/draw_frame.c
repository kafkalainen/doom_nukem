/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/28 16:00:15 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// static void	draw_minimap(t_home *home, t_frame *frame)
// {
// 	unsigned int	i;
// 	unsigned int	j;
// 	t_wall			*temp;

// 	i = 0;
// 	while (i < home->nbr_of_sectors)
// 	{
// 		j = 0;
// 		temp = home->sectors[i]->walls;
// 		while (j < home->sectors[i]->nb_of_walls)
// 		{
// 			if (temp->top.type < 0)
// 			{
// 				draw_line(center_to_screen(temp->point),
// 					center_to_screen(temp->next->point),
// 					get_color(greenyellow), &frame->buffer);
// 			}
// 			else
// 			{
// 				draw_line(center_to_screen(temp->point),
// 					center_to_screen(temp->next->point),
// 					get_color(red), &frame->buffer);
// 			}
// 			temp = temp->next;
// 			j++;
// 		}
// 		i++;
// 	}
// }

// static void	draw_player(t_frame *frame, t_player *plr)
// {
// 	t_xy	offsetpos;

// 	offsetpos = center_to_screen(vec2(plr->pos.x, plr->pos.z));
// 	offsetpos.x -= 5;
// 	offsetpos.y -= 5;
// 	draw_square(&frame->buffer, offsetpos,
// 		get_color(yellow), 10);
// }

// static void	draw_left_right(t_frame *frame,
// t_xy pos, t_xy left, t_xy right, t_uint c)
// {
// 	draw_line(center_to_screen(pos),
// 		center_to_screen(left),
// 		c, &frame->buffer);
// 	draw_line(center_to_screen(pos),
// 		center_to_screen(right),
// 		c, &frame->buffer);
// }

void	draw_frame(t_home *home, t_frame *frame, t_player *plr)
{
	if (plr->plot_state == start_cutscene)
		draw_cutscene(&frame->buffer, plr, home->sectors[plr->start_sector]);
	else if (plr->plot_state == end_cutscene)
		draw_cutscene(&frame->buffer, plr, home->sectors[home->end_sector]);
	else
	{
		frame->idx = plr->cur_sector;
		frame->old_idx = old_sector;
		reset_depth_buffer(frame->depth_buffer);
		draw_game(home, frame, plr);
		// draw_fog()
		if (plr->input.info)
			draw_info(frame, plr, (int)home->t.fps);
		draw_heads_up_display(home, frame, plr);
		draw_plot_state(home, &frame->buffer, plr);
		draw_object_data(&frame->buffer, plr);
	}
	return ;
}
