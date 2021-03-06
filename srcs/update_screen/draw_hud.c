/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:44:14 by tmaarela          #+#    #+#             */
/*   Updated: 2021/10/09 14:12:22 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	draw_power_bar(t_player *plr, t_buffer *buffer, int bg_colour,
			int fg_colour)
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
				wh.y + gap * 0.5), buffer, bg_colour);
		draw_rect(vec2(plr->hud.hud_hp_x + i * (wh.x + gap), plr->hud.hud_hp_y),
			vec2(wh.x, wh.y), buffer, fg_colour);
		i++;
	}
}

static void	draw_fuel_bar(t_player *plr, t_buffer *buffer, int bg_colour,
			int fg_colour)
{
	t_xy			wh;

	wh = vec2(plr->fuel_points * 0.9, 6);
	draw_rect(vec2(plr->hud.hud_fuel_x - 2, plr->hud.hud_fuel_y - 2),
		vec2(wh.x + 4, wh.y + 4), buffer, bg_colour);
	draw_rect(vec2(plr->hud.hud_fuel_x, plr->hud.hud_fuel_y),
		vec2(wh.x, wh.y), buffer, fg_colour);
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
			if (buffer->lightness < 1.0f)
				colour = colour_scale(colour, 1.0f, buffer->lightness, 1.0f);
			put_pixel(buffer, (t_pxl_coords){x, y}, colour);
			x++;
		}
		y++;
	}
}

static void	draw_mission_failed(t_buffer *buffer)
{
	t_plx_modifier	mod;

	mod.colour = 0xFFFFFFFF;
	mod.len = 100;
	mod.size = 4;
	ft_str_pxl(buffer, vec2(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.4f),
		"MISSION::FAILED", mod);
}

void	draw_heads_up_display(t_home *home, t_frame *frame, t_player *plr)
{
	Uint32			bg_colour;
	Uint32			fg_colour;

	bg_colour = 0;
	fg_colour = 0;
	calc_colours(&bg_colour, &fg_colour, &frame->buffer.lightness);
	if (plr->wep[plr->active_wep].ammo > 0
		&& plr->wep[plr->active_wep].fire_rate > 450)
		draw_muzzleflash(home, &frame->buffer, plr,
			vec2(plr->hud.vm_x, plr->hud.vm_y + 32));
	draw_weapon(home, &frame->buffer, plr,
		vec2(plr->hud.vm_x, plr->hud.vm_y));
	draw_hud_image(home, &frame->buffer);
	draw_power_bar(plr, &frame->buffer, bg_colour, fg_colour);
	draw_fuel_bar(plr, &frame->buffer, bg_colour, fg_colour);
	draw_inventory_slots(plr, &frame->buffer);
	draw_inventory_images(home, plr, &frame->buffer);
	draw_hud_ammo_left(&frame->buffer, plr);
	draw_crosshair(&frame->buffer);
	if (plr->dead > 0)
		draw_mission_failed(&frame->buffer);
}
