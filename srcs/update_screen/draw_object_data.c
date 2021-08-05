/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_object_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:00:10 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/05 15:11:04 by jnivala          ###   ########.fr       */
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
	else if (plr->display_object == button)
		ft_str_pxl(buffer, (t_xy){SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.1f},
			"Button: Press F to activate.", mod);
	else
		return ;
}
