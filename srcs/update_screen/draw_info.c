/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:52:05 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/04 16:31:41 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	compass_direction(t_buffer *buffer, t_xy *dir, t_plx_modifier mod)
{
	t_xy	center;

	center.x = SCREEN_WIDTH * 0.5f - (mod.size * 5 * 5);
	center.y = SCREEN_HEIGHT * 0.05f;
	if (dir->x <= NW && dir->x > 0)
		ft_str_pxl(buffer, center, "::North::", mod);
	else if (dir->x <= N && dir->x > NE)
		ft_str_pxl(buffer, center, "::North::", mod);
	else if (dir->x <= SW && dir->x > NW)
	{
		center.x += mod.size * 5 * 0.5f;
		ft_str_pxl(buffer, center, "::West::", mod);
	}
	else if (dir->x <= SE && dir->x > SW)
		ft_str_pxl(buffer, center, "::South::", mod);
	else if (dir->x <= NE && dir->x > SE)
	{
		center.x += mod.size * 5 * 0.5f;
		ft_str_pxl(buffer, center, "::East::", mod);
	}
	else
		ft_str_pxl(buffer, center, "::No dir::", mod);
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
// draw_coordinate(&frame->buffer, plr->pos, plr->cur_sector);
void	draw_info(t_frame *frame, t_player *plr, int nb_fps)
{
	char			*fps;
	t_plx_modifier	mod;

	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	mod.len = 100;
	fps = ft_itoa(nb_fps);
	ft_str_pxl(&frame->buffer, vec2(SCREEN_WIDTH * 0.5 - 15, 0), fps, mod);
	compass_direction(&frame->buffer, &plr->dir, mod);
	ft_str_pxl(&frame->buffer, vec2(10, 280), "1 2 3 4 to select item", mod);
	ft_str_pxl(&frame->buffer, vec2(10, 300), "f to use item", mod);
	ft_str_pxl(&frame->buffer, vec2(10, 320), "c to close info", mod);
	ft_str_pxl(&frame->buffer, vec2(10, 340), "z to pause music", mod);
	ft_str_pxl(&frame->buffer, vec2(10, 360), "wasd, rotate with q and e.",
		mod);
	ft_str_pxl(&frame->buffer, vec2(10, 380), "free mouse with m", mod);
	ft_str_pxl(&frame->buffer, vec2(10, 400), "shoot with left mouse", mod);
	ft_str_pxl(&frame->buffer, vec2(10, 420), "fly with right mouse", mod);
	ft_str_pxl(&frame->buffer, vec2(10, 440), "jump with space", mod);
	ft_str_pxl(&frame->buffer, vec2(10, 460), "crouch with left ctrl", mod);
	free(fps);
}
