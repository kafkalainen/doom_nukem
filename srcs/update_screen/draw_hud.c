/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:44:14 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/30 14:02:26 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	draw_power_bar(t_player *plr, t_buffer *buffer)
{
	int				i;
	t_xy			wh;
	int				gap;

	i = 0;
	gap = 4;
	wh = vec2(12, 21);
	while (i < (int)(plr->power_points + 0.99))
	{
		draw_rect(vec2(plr->hud.hud_hp_x + i * (wh.x + gap) - gap * 0.25,
				plr->hud.hud_hp_y - gap * 0.25), vec2(wh.x + gap * 0.5,
				wh.y + gap * 0.5), buffer, 0xFFFFFFFF);
		draw_rect(vec2(plr->hud.hud_hp_x + i * (wh.x + gap), plr->hud.hud_hp_y),
			vec2(wh.x, wh.y), buffer, 0xFFFFEA00);
		i++;
	}
}

static void	draw_fuel_bar(t_player *plr, t_buffer *buffer)
{
	t_xy			wh;

	wh = vec2(plr->fuel_points * 0.9, 6);
	draw_rect(vec2(plr->hud.hud_fuel_x - 2, plr->hud.hud_fuel_y - 2),
		vec2(wh.x + 4, wh.y + 4), buffer, 0xFFFFFFFF);
	draw_rect(vec2(plr->hud.hud_fuel_x, plr->hud.hud_fuel_y),
		vec2(wh.x, wh.y), buffer, 0xFFFFEA00);
}

static void	draw_hud_image(t_home *home, t_buffer *buffer)
{
	int				x;
	int				y;
	t_texel			tex;
	Uint32			colour;

	tex = home->textures[hud]->tex;
	y = 0;
	while (y < tex.height)
	{
		x = 0;
		while (x < tex.width)
		{
			colour = (Uint32)tex.texels[(tex.width * y) + x];
			put_pixel(buffer, (t_pxl_coords){x, y}, colour);
				// colour_scale(colour, 1.0f, buffer->lightness));
			x++;
		}
		y++;
	}
}

static void	draw_mission_failed(t_buffer *buffer)
{
	t_plx_modifier	mod;

	mod.colour = white;
	mod.len = 100;
	mod.size = 4;
	ft_str_pxl(buffer, vec2(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.4f),
		"MISSION::FAILED", mod);
}

void	draw_heads_up_display(t_home *home, t_frame *frame, t_player *plr)
{
	if (plr->wep[plr->active_wep].fire_rate > 0.45)
		draw_muzzleflash(home, &frame->buffer, plr,
			vec2(plr->hud.vm_x, plr->hud.vm_y + 32));
	draw_weapon(home, &frame->buffer, plr,
		vec2(plr->hud.vm_x, plr->hud.vm_y));
	draw_hud_image(home, &frame->buffer);
	draw_power_bar(plr, &frame->buffer);
	draw_fuel_bar(plr, &frame->buffer);
	draw_inventory_slots(plr, &frame->buffer);
	draw_inventory_images(home, plr, &frame->buffer);
	draw_hud_ammo_left(&frame->buffer, plr);
	draw_crosshair(&frame->buffer);
	if (plr->dead > 0)
		draw_mission_failed(&frame->buffer);
}
