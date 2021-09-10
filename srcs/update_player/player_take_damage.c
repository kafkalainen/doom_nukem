/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_take_damage.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 12:15:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/10 12:09:33 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	player_take_damage(t_player *plr, Uint32 damage, Uint32 time)
{
	if (!plr)
		return ;
	if (plr->power_points)
		plr->power_points -= damage;
	play_sound(plr->audio.rahikainen_damage[time % 3], 20);
	if (plr->power_points < 2)
		play_sound(plr->audio.battery_low, 30);
}
