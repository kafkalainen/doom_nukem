/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:44:14 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/02 15:22:48 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void		draw_hud_texts(Uint32 *buffer, t_player *plr)
{
	char			*str;
	t_plx_modifier	mod;

	mod.colour = get_color(white);
	mod.size = 3;
	str = ft_strjoin("Ammo: ", ft_itoa(plr->wep[plr->active_wep].ammo));
	mod.len = ft_strlen(str);
	ft_str_pxl(buffer, vec2(plr->hud.hud_ammo_x, plr->hud.hud_ammo_y),
		str, mod);
	free(str);
}

static void		draw_power_bar(t_player *plr, Uint32 *buffer)
{
	int		i;
	t_xy	wh;
	int		gap;

	i = 0;
	gap = 4;
	wh = vec2(12, 21);
	while (i < (int)(plr->power_points + 0.99))
	{
		draw_rect(vec2(plr->hud.hud_hp_x+ i * (wh.x + gap) - gap * 0.25,
			plr->hud.hud_hp_y - gap * 0.25), vec2(wh.x + gap * 0.5,
			wh.y + gap * 0.5), buffer, 0xFFFFFFFF);
		draw_rect(vec2(plr->hud.hud_hp_x+ i * (wh.x + gap), plr->hud.hud_hp_y),
			vec2(wh.x, wh.y), buffer, 0xFFD42E00);
		i++;
	}
}

static void		draw_fuel_bar(t_player *plr, Uint32 *buffer)
{
	t_xy	wh;

	wh = vec2(plr->fuel_points * 0.9, 6);
	draw_rect(vec2(plr->hud.hud_fuel_x - 2, plr->hud.hud_fuel_y - 2),
		vec2(wh.x + 4, wh.y + 4), buffer, 0xFFFFFFFF);
	draw_rect(vec2(plr->hud.hud_fuel_x, plr->hud.hud_fuel_y),
		vec2(wh.x, wh.y), buffer, 0xFFD42E00);
}

static void		draw_crosshair(Uint32 *buffer)
{
	t_xy	wh;

	wh = vec2(12, 12);
	draw_line(vec2(SCREEN_WIDTH * 0.5 - wh.x * 0.5, SCREEN_HEIGHT * 0.5),
		vec2(SCREEN_WIDTH * 0.5 + wh.x * 0.5, SCREEN_HEIGHT * 0.5),
		0xFF00F180, buffer);
	draw_line(vec2(SCREEN_WIDTH * 0.499, SCREEN_HEIGHT * 0.5 - wh.y * 0.5),
		vec2(SCREEN_WIDTH * 0.499, SCREEN_HEIGHT * 0.5 + wh.y * 0.5),
		0xFF00F180, buffer);
	draw_line(vec2(SCREEN_WIDTH * 0.5 - wh.x * 0.5, SCREEN_HEIGHT * 0.499),
		vec2(SCREEN_WIDTH * 0.5 + wh.x * 0.5, SCREEN_HEIGHT * 0.499),
		0xFF00F180, buffer);
	draw_line(vec2(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5 - wh.y * 0.5),
		vec2(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5 + wh.y * 0.5),
		0xFF00F180, buffer);
}

static void		draw_hud_image(t_home *home, Uint32 *buffer)
{
	int		x;
	int		y;
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

static void		draw_viewmodel_sprite(t_home *home, Uint32 *buffer,
	t_player *plr, t_xy offset)
{
	int		x;
	int		y;
	t_texel	tex;
	tex = home->textures[weapon0]->tex;

	y = 0;
	offset.x += plr->hud.vm_mx * 10 + plr->hud.vm_rx;
	offset.y += plr->hud.vm_my * 10 + plr->hud.vm_ry;
	while (y < tex.height)
	{
		x = 0;
		while (x < tex.width)
		{
			put_pixel(buffer, x + (int)offset.x, y + (int)offset.y,
				(Uint32)tex.texels[(tex.width * y) + x]);
			x++;
		}
		y++;
	}
}

static void		draw_muzzleflash(t_home *home, Uint32 *buffer,
	t_player *plr, t_xy offset)
{
	int		x;
	int		y;
	t_texel	tex;
	tex = home->textures[muzzleflash]->tex;

	y = 0;
	offset.x += plr->hud.vm_mx * 10 + plr->hud.vm_rx;
	offset.y += plr->hud.vm_my * 10 + plr->hud.vm_ry;
	while (y < tex.height)
	{
		x = 0;
		while (x < tex.width)
		{
			put_pixel(buffer, x + (int)offset.x, y + (int)offset.y,
				(Uint32)tex.texels[(tex.width * y) + x]);
			x++;
		}
		y++;
	}
}

static void		draw_uded(Uint32 *buffer)
{
	t_plx_modifier	mod;

	mod.colour = white;
	mod.len = 100;
	mod.size = 4;
	ft_str_pxl(buffer, (t_xy){SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.4f},
			"MISSION::FAILED", mod);
}

void			draw_heads_up_display(t_home *home, t_frame *frame, t_player *plr)
{
	if (plr->wep[plr->active_wep].fire_rate > 0.45)
		draw_muzzleflash(home, frame->buffer, plr,
			vec2(plr->hud.vm_x, plr->hud.vm_y + 32));
	draw_viewmodel_sprite(home, frame->buffer, plr,
		vec2(plr->hud.vm_x, plr->hud.vm_y));
	draw_hud_image(home, frame->buffer);
	draw_power_bar(plr, frame->buffer);
	draw_fuel_bar(plr, frame->buffer);
	draw_inventory_slots(plr, frame->buffer);
	draw_inventory_images(home, plr, frame->buffer);
	draw_hud_texts(frame->buffer, plr);
	draw_crosshair(frame->buffer);
	if (plr->dead > 0)
		draw_uded(frame->buffer);
}
