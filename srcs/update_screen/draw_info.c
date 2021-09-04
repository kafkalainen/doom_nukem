/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:52:05 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/04 12:28:32 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	compass_direction(Uint32 *buffer, t_xy *dir, t_plx_modifier mod)
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

void	draw_info(t_frame *frame, t_player *plr, int nb_fps)
{
	char			*fps;
	char			*plr_pos[3];
	t_plx_modifier	mod;

	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	mod.len = 100;
	fps = ft_itoa(nb_fps);
	plr_pos[0] = ft_ftoa(plr->pos.x, 6);
	plr_pos[1] = ft_ftoa(plr->pos.y, 6);
	plr_pos[2] = ft_ftoa(plr->pos.z, 6);
	ft_str_pxl(frame->buffer, (t_xy){SCREEN_WIDTH * 0.5 - 15, 0}, fps, mod);
	compass_direction(frame->buffer, &plr->dir, mod);
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 150.0f},
		"player_xyz", (t_plx_modifier){get_color(green), 2, 12});
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 170.0f}, plr_pos[0],
		(t_plx_modifier){get_color(green), 2, 12});
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 190.0f}, plr_pos[1],
		(t_plx_modifier){get_color(green), 2, 12});
	ft_str_pxl(frame->buffer, (t_xy){5.0f, 210.0f}, plr_pos[2],
		(t_plx_modifier){get_color(green), 2, 12});
	ft_str_pxl(frame->buffer, (t_xy){0, 400}, "x to close minimap", mod);
	ft_str_pxl(frame->buffer, (t_xy){0, 420}, "c to close info", mod);
	ft_str_pxl(frame->buffer, (t_xy){0, 420}, "z to pause music", mod);
	ft_str_pxl(frame->buffer, (t_xy){0, 440}, "wasd, rotate with q and e.",
		mod);
	ft_str_pxl(frame->buffer, (t_xy){0, 460}, "free mouse with m", mod);
	free(fps);
	free(plr_pos[0]);
	free(plr_pos[1]);
	free(plr_pos[2]);
}
