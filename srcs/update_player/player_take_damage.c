/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_take_damage.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 12:15:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/29 16:06:00 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	update_damage_tick(Uint32 delta_time, int *take_damage)
{
	if (*take_damage > 0)
		*take_damage -= delta_time;
	else
		*take_damage = 0;
}

void	player_take_damage(t_player *plr, Uint32 damage, Uint32 time)
{
	if (!plr)
		return ;
	if (plr->power_points)
		plr->power_points -= damage;
	play_sound(plr->audio.rahikainen_damage[time % 3], 20);
	if (plr->power_points < 2)
		play_sound(plr->audio.battery_low, 30);
	plr->take_damage = 255;
}
