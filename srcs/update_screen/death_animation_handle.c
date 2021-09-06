/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_animation_handle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 12:13:15 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 14:36:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	death_animation(t_home *home, t_player *plr, Uint32 t)
{
	plr->roll = plr->roll - 0.002f * t;
	plr->yaw = plr->yaw + 0.001f * t;
	plr->pitch = plr->pitch + 0.001f * t;
	plr->pos.y -= 0.0015f * t;
	plr->dead += 0.001f * t;
	if (plr->dead > 2)
		home->game_state = MAIN_MENU;
}
