/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:41:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/06 14:54:41 by jnivala          ###   ########.fr       */
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
}

static void	free_sound(Mix_Chunk **chunk)
{
	if (*chunk != NULL)
		Mix_FreeChunk(*chunk);
	*chunk = NULL;
}

static void	cleanup_enemy_audio_sources(t_audio *audio)
{
	free_sound(&audio->skull_skulker_aggro);
	free_sound(&audio->skull_skulker_attack);
	free_sound(&audio->skull_skulker_damage);
	free_sound(&audio->skull_skulker_death);
	free_sound(&audio->thing_aggro);
	free_sound(&audio->thing_attack);
	free_sound(&audio->thing_damage);
	free_sound(&audio->thing_death);
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
	free_sound(&audio->rahikainen_ramble[0]);
	free_sound(&audio->rahikainen_ramble[1]);
	free_sound(&audio->rahikainen_ramble[2]);
	free_sound(&audio->rahikainen_ramble[3]);
	free_sound(&audio->rahikainen_damage[0]);
	free_sound(&audio->rahikainen_damage[1]);
	free_sound(&audio->rahikainen_damage[2]);
	free_sound(&audio->rahikainen_damage[3]);
	free_sound(&audio->rahikainen_damage[4]);
	free_sound(&audio->bolt_locked);
	free_sound(&audio->bolt_unlocked);
	free_sound(&audio->lift);
	free_sound(&audio->plasma_gun_no_ammo);
	free_sound(&audio->reload);
	free_sound(&audio->unlock_door);
	cleanup_enemy_audio_sources(audio);
}
