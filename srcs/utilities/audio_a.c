/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:41:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/10 12:14:29 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	initialize_player_audio_to_null(t_audio *audio)
{
	audio->rahikainen_ramble[0] = NULL;
	audio->rahikainen_ramble[1] = NULL;
	audio->rahikainen_ramble[2] = NULL;
	audio->rahikainen_ramble[3] = NULL;
	audio->rahikainen_damage[0] = NULL;
	audio->rahikainen_damage[1] = NULL;
	audio->rahikainen_damage[2] = NULL;
	audio->rahikainen_damage[3] = NULL;
	audio->rahikainen_damage[4] = NULL;
	audio->rahikainen_die = NULL;
}

void	initialize_audio_to_null(t_audio *audio)
{
	audio->footstep1 = NULL;
	audio->footstep2 = NULL;
	audio->music = NULL;
	audio->door = NULL;
	audio->button = NULL;
	audio->plasma_gun = NULL;
	audio->error = NULL;
	initialize_player_audio_to_null(audio);
	audio->bolt_unlocked = NULL;
	audio->bolt_locked = NULL;
	audio->lift = NULL;
	audio->plasma_gun_no_ammo = NULL;
	audio->reload = NULL;
	audio->unlock_door = NULL;
	audio->skull_skulker_aggro = NULL;
	audio->skull_skulker_attack = NULL;
	audio->skull_skulker_damage = NULL;
	audio->skull_skulker_death = NULL;
	audio->thing_aggro = NULL;
	audio->thing_attack = NULL;
	audio->thing_damage = NULL;
	audio->thing_death = NULL;
	audio->recharge = NULL;
	audio->power_station_depleted = NULL;
	audio->battery_low = NULL;
}
