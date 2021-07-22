/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:44:14 by tmaarela          #+#    #+#             */
/*   Updated: 2021/07/22 12:42:43 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void		draw_hud_texts(Uint32 *buffer, t_player *plr, int slot)
{
	t_plx_modifier	mod;

	mod.colour = get_color(white);
	mod.size = 3;
	ft_str_pxl(buffer, vec2(HUD_AMMO_X, HUD_AMMO_Y - 12),
		ft_strjoin("Ammo: ", ft_itoa(plr->live_ammo[slot])), mod);
	mod.size = 2;
	ft_str_pxl(buffer, vec2(HUD_AMMO_X + 100, HUD_AMMO_Y + 12),
		ft_itoa(plr->reserve_ammo[slot]), mod);
}

static void		draw_power_bar(t_player *plr, Uint32 *buffer)
{
	int		i;
	t_xy	wh;
	int		gap;

	i = 0;
	gap = 8;
	wh = vec2(14, 42);
	while (i < (int)(plr->power_points + 0.99))
	{
		draw_rect(vec2(HUD_HP_X + i * (wh.x + gap) - gap * 0.25,
			HUD_HP_Y - gap * 0.25), vec2(wh.x + gap * 0.5,
			wh.y + gap * 0.5), buffer, 0xFF00AEFF);
		draw_rect(vec2(HUD_HP_X + i * (wh.x + gap), HUD_HP_Y),
			vec2(wh.x, wh.y), buffer, 0xFF0060D4);
		i++;
	}
}

static void		draw_inventory_slots(t_player *plr, Uint32 *buffer)
{
	int		i;
	t_xy	wh;
	int		gap;

	i = -2;
	gap = 12;
	wh = vec2(32, 32);
	while (i < 2)
	{
		if (plr->active_inv == i + 2)
			draw_rect(vec2(SCREEN_WIDTH * 0.5 + i * (wh.x + gap) - gap * 0.25,
				HUD_HP_Y + 8 - gap * 0.25), vec2(wh.x + gap * 0.5, wh.y + gap * 0.5), buffer, 0xFFDDDD00);
		else
			draw_rect(vec2(SCREEN_WIDTH * 0.5 + i * (wh.x + gap) - gap * 0.25,
				HUD_HP_Y + 8 - gap * 0.25), vec2(wh.x + gap * 0.5, wh.y + gap * 0.5), buffer, 0xFF202020);
		draw_rect(vec2(SCREEN_WIDTH * 0.5 + i * (wh.x + gap),
			HUD_HP_Y + 8), vec2(wh.x, wh.y), buffer, 0xFF606060);
		i++;
	}
}

static void		draw_hud_image(t_home *home, Uint32 *buffer)
{
	Uint32	x;
	Uint32	y;
	t_texel	tex;
	tex = home->textures[hud]->tex;

	y = 0;
	while (y < tex.height)
	{
		x = 0;
		while (x < tex.width)
		{
			put_pixel(buffer, x, y, (Uint32)tex.texels[(tex.width * y) + x]);
			x++;
		}
		y++;
	}
}

void			draw_heads_up_display(t_home *home, t_frame *frame, t_player *plr)
{
	(void)home;
	draw_hud_image(home, frame->buffer);
	draw_power_bar(plr, frame->buffer);
	draw_inventory_slots(plr, frame->buffer);
	//draw_inventory_images(home, frame, plr);
	draw_hud_texts(frame->buffer, plr, 0);
}
