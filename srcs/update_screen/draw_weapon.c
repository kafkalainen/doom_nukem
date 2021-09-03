/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:27:55 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 14:34:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_hud_ammo_left(Uint32 *buffer, t_player *plr)
{
	char			*str;
	char			*concatstr;
	t_plx_modifier	mod;

	mod.colour = get_color(white);
	mod.size = 3;
	str = ft_itoa(plr->wep[plr->active_wep].ammo);
	concatstr = ft_strjoin("Ammo: ", str);
	free(str);
	mod.len = ft_strlen(concatstr);
	ft_str_pxl(buffer, vec2(plr->hud.hud_ammo_x, plr->hud.hud_ammo_y),
		concatstr, mod);
	free(concatstr);
}

void	draw_crosshair(Uint32 *buffer)
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

void	draw_weapon(t_home *home, Uint32 *buffer,
		t_player *plr, t_xy offset)
{
	int		x;
	int		y;
	t_texel	tex;

	y = 0;
	tex = home->textures[weapon0]->tex;
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

void	draw_muzzleflash(t_home *home, Uint32 *buffer,
			t_player *plr, t_xy offset)
{
	int		x;
	int		y;
	t_texel	tex;

	y = 0;
	tex = home->textures[muzzleflash]->tex;
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
