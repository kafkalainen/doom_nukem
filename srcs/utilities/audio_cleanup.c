/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:07:50 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/29 11:34:05 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	free_sound(Mix_Chunk **chunk)
{
	if (*chunk != NULL)
		Mix_FreeChunk(*chunk);
	*chunk = NULL;
}

static void	cleanup_enemy_audio_sources(t_audio *audio)
{
	free_sound(&audio->skull_skulker_lulling);
	free_sound(&audio->skull_skulker_aggro);
	free_sound(&audio->skull_skulker_attack);
	free_sound(&audio->skull_skulker_damage);
	free_sound(&audio->skull_skulker_death);
	free_sound(&audio->thing_lulling);
	free_sound(&audio->thing_aggro);
	free_sound(&audio->thing_attack);
	free_sound(&audio->thing_damage);
	free_sound(&audio->thing_death);
}

static void	cleanup_rahikainen_audio_sources(t_audio *audio)
{
	free_sound(&audio->rahikainen_ramble[0]);
	free_sound(&audio->rahikainen_ramble[1]);
	free_sound(&audio->rahikainen_ramble[2]);
	free_sound(&audio->rahikainen_ramble[3]);
	free_sound(&audio->rahikainen_damage[0]);
	free_sound(&audio->rahikainen_damage[1]);
	free_sound(&audio->rahikainen_damage[2]);
	free_sound(&audio->rahikainen_damage[3]);
	free_sound(&audio->rahikainen_damage[4]);
	free_sound(&audio->rahikainen_die);
}

void	cleanup_audio_source(t_audio *audio)
{
	if (Mix_PlayingMusic())
		Mix_PauseMusic();
	if (audio->music != NULL)
		Mix_FreeMusic(audio->music);
	audio->music = NULL;
	free_sound(&audio->footstep1);
	free_sound(&audio->footstep2);
	free_sound(&audio->door);
	free_sound(&audio->button);
	free_sound(&audio->plasma_gun);
	free_sound(&audio->error);
	free_sound(&audio->bolt_locked);
	free_sound(&audio->bolt_unlocked);
	free_sound(&audio->lift);
	free_sound(&audio->plasma_gun_no_ammo);
	free_sound(&audio->reload);
	free_sound(&audio->unlock_door);
	free_sound(&audio->power_station_depleted);
	free_sound(&audio->recharge);
	free_sound(&audio->battery_low);
	free_sound(&audio->typing);
	cleanup_rahikainen_audio_sources(audio);
	cleanup_enemy_audio_sources(audio);
}
