/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:27:55 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 15:14:47 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_hud_ammo_left(t_buffer *buffer, t_player *plr)
{
	char			*str;
	char			*concatstr;
	t_plx_modifier	mod;

	if (buffer->lightness < 1.0f)
		mod.colour = colour_scale(0xFFFFFFFF, 1.0f, buffer->lightness, 1.0f);
	else
		mod.colour = 0xFFFFFFFF;
	mod.size = 3;
	str = ft_itoa(plr->wep[plr->active_wep].ammo);
	concatstr = ft_strjoin("Ammo: ", str);
	free(str);
	mod.len = ft_strlen(concatstr);
	ft_str_pxl(buffer, vec2(plr->hud.hud_ammo_x, plr->hud.hud_ammo_y),
		concatstr, mod);
	free(concatstr);
}

void	draw_crosshair(t_buffer *buffer)
{
	t_pxl_coords	start;
	t_pxl_coords	end;
	Uint32			colour;

	start.y = SCREEN_HEIGHT * 0.5f - 8;
	end.y = SCREEN_HEIGHT * 0.5f + 8;
	start.x = SCREEN_WIDTH * 0.5f;
	if (buffer->lightness < 1.0f)
		colour = colour_scale(0xFFFFCC00, 1.0f, buffer->lightness, 1.0f);
	else
		colour = 0xFFFFCC00;
	while (start.y < end.y)
	{
		put_pixel(buffer, start, colour);
		put_pixel(buffer, (t_pxl_coords){start.x - 1, start.y}, colour);
		put_pixel(buffer, (t_pxl_coords){start.x + 1, start.y}, colour);
		start.y++;
	}
	start.x = SCREEN_WIDTH * 0.5f - 8;
	end.x = SCREEN_WIDTH * 0.5f + 8;
	start.y = SCREEN_HEIGHT * 0.5f;
	while (start.x < end.x)
	{
		put_pixel(buffer, start, colour);
		put_pixel(buffer, (t_pxl_coords){start.x, start.y - 1}, colour);
		put_pixel(buffer, (t_pxl_coords){start.x, start.y + 1}, colour);
		start.x++;
	}
}

void	draw_weapon(t_home *home, t_buffer *buffer,
		t_player *plr, t_xy offset)
{
	int		x;
	int		y;
	t_texel	tex;
	Uint32	colour;

	y = 0;
	tex = home->textures[weapon0]->tex;
	offset.x += plr->hud.vm_mx * 10 + plr->hud.vm_rx;
	offset.y += plr->hud.vm_my * 10 + plr->hud.vm_ry;
	while (y < tex.height)
	{
		x = 0;
		while (x < tex.width)
		{
			colour = (Uint32)tex.texels[(tex.width * y) + x];
			if (buffer->lightness < 1.0f)
				colour = colour_scale(colour, 1.0f, buffer->lightness, 1.0f);
			put_pixel(buffer,
				(t_pxl_coords){x + (int)offset.x, y + (int)offset.y},
				colour);
			x++;
		}
		y++;
	}
}

void	draw_muzzleflash(t_home *home, t_buffer *buffer,
			t_player *plr, t_xy offset)
{
	int		x;
	int		y;
	t_texel	tex;
	Uint32	colour;

	y = 0;
	tex = home->textures[muzzleflash]->tex;
	offset.x += plr->hud.vm_mx * 10 + plr->hud.vm_rx;
	offset.y += plr->hud.vm_my * 10 + plr->hud.vm_ry;
	while (y < tex.height)
	{
		x = 0;
		while (x < tex.width)
		{
			colour = (Uint32)tex.texels[(tex.width * y) + x];
			if (buffer->lightness < 1.0f)
				colour = colour_scale(colour, 1.0f, buffer->lightness, 1.0f);
			put_pixel(buffer,
				(t_pxl_coords){x + (int)offset.x, y + (int)offset.y},
				colour);
			x++;
		}
		y++;
	}
}
