/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_object_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:00:10 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/01 18:14:50 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_object_data(Uint32 *buffer, t_player *plr)
{
	t_plx_modifier	mod;

	mod.colour = white;
	mod.len = 100;
	mod.size = TEXT_SIZE;
	if (plr->display_object == powerstation)
		ft_str_pxl(buffer, (t_xy){SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.1f},
			"Power station: Press F to charge.", mod);
	else if (plr->display_object == light_button)
		ft_str_pxl(buffer, (t_xy){SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.1f},
			"Button: Press F to turn on lights.", mod);
	else if (plr->display_object == elevator_button)
		ft_str_pxl(buffer, (t_xy){SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.1f},
			"Button: Press F to activate the elevator.", mod);
	else if (plr->display_object == keycard_cleaning)
		ft_str_pxl(buffer, (t_xy){SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.1f},
			"Keycard: Press F to pickup cleaning keycard.", mod);
	else if (plr->display_object == keycard_engineering)
		ft_str_pxl(buffer, (t_xy){SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.1f},
			"Keycard: Press F to pickup engineering keycard.", mod);
	else if (plr->display_object == keycard_military)
		ft_str_pxl(buffer, (t_xy){SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.1f},
			"Keycard: Press F to pickup military keycard.", mod);
	else if (plr->display_object == ammo_pack)
		ft_str_pxl(buffer, (t_xy){SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.1f},
			"Ammo pack: Press F to reload plasma pistol.", mod);
	else
		return ;
}
