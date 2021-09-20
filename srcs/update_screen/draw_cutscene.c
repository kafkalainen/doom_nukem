/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cutscene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 09:40:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/20 17:19:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	draw_header(t_buffer *buffer, t_sector *sector)
{
	t_plx_modifier	mod;
	t_xy			offset;
	char			*temp;

	mod.size = 4;
	mod.colour = get_color(limegreen);
	temp = sector->story[0];
	temp += 8;
	mod.len = ft_strlen(temp);
	offset.x = 0.5f * (buffer->width - (mod.len * mod.size * 5));
	if (mod.len % 2)
		offset.x -= (mod.size * 5 * 0.5f);
	offset.y = 100;
	ft_str_pxl(buffer, offset, temp, mod);
}

static void	draw_previous_lines(t_buffer *buffer, t_sector *sector)
{
	t_plx_modifier	mod;
	t_xy			offset;
	int				msgs;

	mod.size = TEXT_SIZE;
	mod.colour = get_color(limegreen);
	msgs = sector->cur_msg - 1;
	while (msgs--)
	{
		mod.len = ft_strlen(sector->story[msgs]);
		offset.x = 0.5f * (buffer->width - (mod.len * mod.size * 5));
		if (mod.len % 2)
			offset.x -= (mod.size * 5 * 0.5f);
		offset.y = 200 + msgs * 7 * mod.size;
		ft_str_pxl(buffer, offset, sector->story[msgs], mod);
	}
}

static void	draw_current_line(t_buffer *buffer, t_player *plr, t_sector *sector)
{
	float			percentage;
	t_xy			offset;
	t_plx_modifier	mod;

	mod.size = TEXT_SIZE;
	mod.colour = get_color(limegreen);
	percentage = 1.0f - plr->cutscene / (float)plr->cutscene_total;
	mod.len = (size_t)(ft_strlen(sector->story[sector->cur_msg]) * percentage);
	if (mod.len > 0)
	{
		offset.x = 0.5f * (buffer->width - (mod.len * mod.size * 5));
		if (mod.len % 2)
			offset.x -= (mod.size * 5 * 0.5f);
		offset.y = 200 + sector->cur_msg * 7 * mod.size;
		ft_str_pxl(buffer, offset, sector->story[sector->cur_msg], mod);
	}
}

void	draw_cutscene(t_buffer *buffer, t_player *plr, t_sector *sector)
{
	if (ft_strnstr(sector->story[0], "header. ", 8))
		draw_header(buffer, sector);
	if (sector->cur_msg > 0)
		draw_previous_lines(buffer, sector);
	draw_current_line(buffer, plr, sector);
}
