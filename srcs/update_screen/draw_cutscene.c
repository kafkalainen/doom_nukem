/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cutscene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 09:40:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/06 19:59:45 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	draw_header(t_buffer *buffer, t_sector *sector)
{
	t_xy			offset;
	t_plx_modifier	mod;
	char			*temp;

	temp = sector->story[0];
	temp += 8;
	mod.len = ft_strlen(temp);
	mod.size = 4;
	mod.colour = 0xFFFFFF00;
	if (mod.len > 90)
		mod.len = 90;
	offset.x = center_text_x_axis(0, buffer->width, mod.size, mod.len);
	offset.y = 100;
	ft_str_pxl(buffer, offset, temp, mod);
}

static void	draw_previous_lines(t_buffer *buffer, t_sector *sector)
{
	t_plx_modifier	mod;
	t_xy			offset;
	int				msgs;

	mod.size = TEXT_SIZE;
	mod.colour = 0xFFFFCC00;
	msgs = sector->cur_msg;
	while (msgs-- > 1)
	{
		mod.len = ft_strlen(sector->story[msgs]);
		if (mod.len > 90)
			mod.len = 90;
		offset.x = center_text_x_axis(0, buffer->width, mod.size, mod.len);
		offset.y = 150 + msgs * 7 * mod.size;
		ft_str_pxl(buffer, offset, sector->story[msgs], mod);
	}
}

static void	draw_current_line(t_buffer *buffer, t_player *plr, t_sector *sector)
{
	t_plx_modifier	mod;
	t_xy			offset;
	float			percentage;

	mod.size = TEXT_SIZE;
	mod.colour = 0xFFFFCC00;
	if (sector->cur_msg < sector->nb_of_msgs)
	{
		percentage = 1.0f - plr->cutscene / (float)plr->cutscene_total;
		mod.len = (size_t)(ft_strlen(sector->story[sector->cur_msg])
				* percentage);
		if (mod.len > 90)
			mod.len = 90;
		if (mod.len > 0 && sector->cur_msg != 0)
		{
			offset.x = center_text_x_axis(0, buffer->width, mod.size, mod.len);
			offset.y = 150 + sector->cur_msg * 7 * mod.size;
			ft_str_pxl(buffer, offset, sector->story[sector->cur_msg], mod);
		}
	}
}

void	draw_cutscene(t_buffer *buffer, t_player *plr, t_sector *sector)
{
	t_plx_modifier	mod;
	t_xy			offset;

	mod.size = TEXT_SIZE;
	mod.colour = 0xFFFFCC00;
	if (sector->story
		&& ft_strnstr(sector->story[0], "header. ", 8))
		draw_header(buffer, sector);
	if (sector->nb_of_msgs > 2 && sector->cur_msg > 1)
		draw_previous_lines(buffer, sector);
	if (sector->nb_of_msgs > 1 && sector->cur_msg > 0)
		draw_current_line(buffer, plr, sector);
	else if (sector->nb_of_msgs == 1)
		draw_current_line(buffer, plr, sector);
	offset.x = center_text_x_axis(0, buffer->width, mod.size, 28);
	offset.y = 570;
	ft_str_pxl(buffer, offset, "Press space to skip cutscene", mod);
}
