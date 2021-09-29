/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:23:12 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/29 11:33:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	load_rahikainen(t_audio *audio)
{
	audio->rahikainen_ramble[0] = Mix_LoadWAV("temp/rahikainen_1.wav");
	audio->rahikainen_ramble[1] = Mix_LoadWAV("temp/rahikainen_2.wav");
	audio->rahikainen_ramble[2] = Mix_LoadWAV("temp/rahikainen_3.wav");
	audio->rahikainen_ramble[3] = Mix_LoadWAV("temp/rahikainen_4.wav");
	audio->rahikainen_damage[0] = Mix_LoadWAV("temp/rahikainen_aah_1.wav");
	audio->rahikainen_damage[1] = Mix_LoadWAV("temp/rahikainen_ugh.wav");
	audio->rahikainen_damage[2] = Mix_LoadWAV("temp/rahikainen_ugh_2.wav");
	audio->rahikainen_damage[3] = Mix_LoadWAV("temp/rahikainen_ugh_3.wav");
	audio->rahikainen_damage[4] = Mix_LoadWAV("temp/rahikainen_damage.wav");
	audio->rahikainen_die = Mix_LoadWAV("temp/rahikainen_die.wav");
	audio->typing = Mix_LoadWAV("temp/typing.wav");
}

static void	load_enemy(t_audio *audio)
{
	audio->skull_skulker_lulling
		= Mix_LoadWAV("temp/skull_skulker_lulling.wav");
	audio->skull_skulker_aggro = Mix_LoadWAV("temp/skull_skulker_aggro.wav");
	audio->skull_skulker_attack = Mix_LoadWAV("temp/skull_skulker_attack.wav");
	audio->skull_skulker_damage = Mix_LoadWAV("temp/skull_skulker_damage.wav");
	audio->skull_skulker_death = Mix_LoadWAV("temp/skull_skulker_death.wav");
	audio->thing_lulling = Mix_LoadWAV("temp/thing_lulling.wav");
	audio->thing_aggro = Mix_LoadWAV("temp/thing_aggro.wav");
	audio->thing_attack = Mix_LoadWAV("temp/thing_attack.wav");
	audio->thing_damage = Mix_LoadWAV("temp/thing_damage.wav");
	audio->thing_death = Mix_LoadWAV("temp/thing_die.wav");
}

static t_bool	check_invalid_pointers(t_audio *audio)
{
	if (!audio->music || !audio->footstep1 || !audio->footstep2
		|| !audio->door || !audio->button || !audio->plasma_gun
		|| !audio->error || !audio->lift || !audio->bolt_locked
		|| !audio->bolt_unlocked || !audio->plasma_gun_no_ammo
		|| !audio->reload || !audio->unlock_door
		|| !audio->skull_skulker_lulling
		|| !audio->skull_skulker_aggro || !audio->skull_skulker_attack
		|| !audio->skull_skulker_damage || !audio->skull_skulker_death
		|| !audio->thing_aggro || !audio->thing_attack || !audio->thing_lulling
		|| !audio->thing_damage || !audio->thing_death
		|| !audio->recharge || !audio->power_station_depleted
		|| !audio->battery_low || !audio->rahikainen_ramble[0]
		|| !audio->rahikainen_ramble[1] || !audio->rahikainen_ramble[2]
		|| !audio->rahikainen_ramble[3] || !audio->rahikainen_damage[0]
		|| !audio->rahikainen_damage[1] || !audio->rahikainen_damage[2]
		|| !audio->rahikainen_damage[3] || !audio->rahikainen_damage[4]
		|| !audio->rahikainen_die || !audio->typing)
		return (true);
	else
		return (false);
}

static void	load_door_effects(t_audio *audio)
{
	audio->door = Mix_LoadWAV("temp/door_opens_and_closes.wav");
	audio->bolt_locked = Mix_LoadWAV("temp/bolt_locked.wav");
	audio->bolt_unlocked = Mix_LoadWAV("temp/bolt_unlocked.wav");
	audio->unlock_door = Mix_LoadWAV("temp/door_unlocked.wav");
}

int	load_game_audio(t_audio *audio)
{
	cleanup_audio_source(audio);
	audio->music = Mix_LoadMUS("temp/eerie_by_eparviai.wav");
	audio->footstep1 = Mix_LoadWAV("temp/footstep1.wav");
	audio->footstep2 = Mix_LoadWAV("temp/footstep2.wav");
	audio->button = Mix_LoadWAV("temp/button.wav");
	audio->plasma_gun = Mix_LoadWAV("temp/plasma_gun.wav");
	audio->error = Mix_LoadWAV("temp/error.wav");
	load_rahikainen(audio);
	load_enemy(audio);
	load_door_effects(audio);
	audio->lift = Mix_LoadWAV("temp/lift.wav");
	audio->plasma_gun_no_ammo = Mix_LoadWAV("temp/out_of_ammo.wav");
	audio->reload = Mix_LoadWAV("temp/reload.wav");
	audio->recharge = Mix_LoadWAV("temp/charging_suit.wav");
	audio->power_station_depleted
		= Mix_LoadWAV("temp/power_station_depleted.wav");
	audio->battery_low = Mix_LoadWAV("temp/battery_low.wav");
	if (check_invalid_pointers(audio))
	{
		ft_putendl("ERROR: Couldn't load audio.");
		return (1);
	}
	return (0);
}
