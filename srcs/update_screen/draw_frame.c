/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/10/01 14:21:24 by rzukale          ###   ########.fr       */
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

// Debugging utility function.
// static void	draw_coordinate(t_buffer *buffer, t_xyz pos, int sector)
// {
// 	char	*pstr[3];
// 	char	*sec;

// 	ft_str_pxl(buffer, vec2(5.0f, 110.0f),
// 		"sector", (t_plx_modifier){get_color(green), 2, 6});
// 	sec = ft_itoa(sector);
// 	ft_str_pxl(buffer, vec2(5.0f, 130.0f),
// 		sec, (t_plx_modifier){get_color(green), 2, 12});
// 	ft_str_pxl(buffer, vec2(5.0f, 150.0f),
// 		"xyz", (t_plx_modifier){get_color(green), 2, 12});
// 	pstr[0] = ft_ftoa(pos.x, 6);
// 	pstr[1] = ft_ftoa(pos.y, 6);
// 	pstr[2] = ft_ftoa(pos.z, 6);
// 	ft_str_pxl(buffer, vec2(5.0f, 170.0f), pstr[0],
// 		(t_plx_modifier){get_color(green), 2, 12});
// 	ft_str_pxl(buffer, vec2(5.0f, 190.0f), pstr[1],
// 		(t_plx_modifier){get_color(green), 2, 12});
// 	ft_str_pxl(buffer, vec2(5.0f, 210.0f), pstr[2],
// 		(t_plx_modifier){get_color(green), 2, 12});
// 	free(pstr[0]);
// 	free(pstr[1]);
// 	free(pstr[2]);
// 	free(sec);
// }

// draw_coordinate(&frame->buffer, home->entity_pool[0]->pos,
// home->entity_pool[0]->sector_idx);
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
