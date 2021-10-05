/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_object_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:00:10 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/05 11:55:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	draw_object_data_pickable(t_buffer *buffer, t_xy loc, t_player *plr,
			t_plx_modifier mod)
{
	if (plr->display_object == keycard_cleaning)
	{
		mod.len = 44;
		loc.x = center_text_x_axis(0, buffer->width, mod.size, mod.len);
		ft_str_pxl(buffer, loc,
			"Keycard: Press F to pickup cleaning keycard.", mod);
	}
	else if (plr->display_object == keycard_engineering)
	{
		mod.len = 47;
		loc.x = center_text_x_axis(0, buffer->width, mod.size, mod.len);
		ft_str_pxl(buffer, loc,
			"Keycard: Press F to pickup engineering keycard.", mod);
	}
	else if (plr->display_object == keycard_military)
	{
		mod.len = 44;
		loc.x = center_text_x_axis(0, buffer->width, mod.size, mod.len);
		ft_str_pxl(buffer, loc,
			"Keycard: Press F to pickup military keycard.", mod);
	}
}

static void	draw_object_data_buttons(t_buffer *buffer, t_xy loc, t_player *plr,
			t_plx_modifier mod)
{
	if (plr->display_object == light_button)
	{
		mod.len = 34;
		loc.x = center_text_x_axis(0, buffer->width, mod.size, mod.len);
		ft_str_pxl(buffer, loc, "Button: Press F to turn on lights.", mod);
	}
	else if (plr->display_object == lift_button)
	{
		mod.len = 37;
		loc.x = center_text_x_axis(0, buffer->width, mod.size, mod.len);
		ft_str_pxl(buffer, loc, "Button: Press F to activate the lift.", mod);
	}
	else if (plr->display_object == ammo_pack)
	{
		mod.len = 46;
		loc.x = center_text_x_axis(0, buffer->width, mod.size, mod.len);
		ft_str_pxl(buffer, loc,
			"Ammo pack: Press F to pickup plasma cartridge.", mod);
	}
}

static void	draw_object_data_door(t_buffer *buffer, t_xy loc, t_player *plr,
			t_plx_modifier mod)
{
	int			idx;
	const int	tab[] = {22, 10, 50, 53, 50};
	const char	*messages[] = {"Door: Press F to open.", "::LOCKED::",
		"::LOCKED Access authorized with cleaning keycard::",
		"::LOCKED Access authorized with engineering keycard::",
		"::LOCKED Access authorized with military keycard::"};

	if (plr->display_object >= unlocked
		&& plr->display_object <= military_lock)
	{
		idx = plr->display_object - 300;
		mod.len = tab[idx];
		loc.x = center_text_x_axis(0, buffer->width, mod.size, mod.len);
		ft_str_pxl(buffer, loc, (char *)messages[idx], mod);
	}
}

void	draw_object_data(t_buffer *buffer, t_player *plr)
{
	t_xy			loc;
	t_plx_modifier	mod;

	mod.colour = white;
	mod.size = TEXT_SIZE;
	loc.y = buffer->height * 0.1f;
	if (plr->display_object == powerstation)
	{
		mod.len = 33;
		loc.x = center_text_x_axis(0, buffer->width, mod.size, mod.len);
		ft_str_pxl(buffer, loc, "Power station: Press F to charge.", mod);
	}
	else if (plr->display_object == light_button
		|| plr->display_object == lift_button
		|| plr->display_object == ammo_pack)
		draw_object_data_buttons(buffer, loc, plr, mod);
	else if (plr->display_object >= keycard_cleaning
		&& plr->display_object <= keycard_military)
		draw_object_data_pickable(buffer, loc, plr, mod);
	else if (plr->display_object >= unlocked
		&& plr->display_object <= military_lock)
		draw_object_data_door(buffer, loc, plr, mod);
	else
		return ;
}
