/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:23:12 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/05 21:42:38 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	load_rahikainen(t_audio *audio)
{
	audio->rahikainen_ramble[0] = Mix_LoadWAV("audio/rahikainen_1.wav");
	audio->rahikainen_ramble[1] = Mix_LoadWAV("audio/rahikainen_2.wav");
	audio->rahikainen_ramble[2] = Mix_LoadWAV("audio/rahikainen_3.wav");
	audio->rahikainen_ramble[3] = Mix_LoadWAV("audio/rahikainen_4.wav");
	audio->rahikainen_damage[0] = Mix_LoadWAV("audio/rahikainen_aah_1.wav");
	audio->rahikainen_damage[1] = Mix_LoadWAV("audio/rahikainen_damage.wav");
	audio->rahikainen_damage[2] = Mix_LoadWAV("audio/rahikainen_ugh.wav");
	audio->rahikainen_damage[3] = Mix_LoadWAV("audio/rahikainen_ugh_2.wav");
	audio->rahikainen_damage[4] = Mix_LoadWAV("audio/rahikainen_ugh_3.wav");
}

static t_bool	check_invalid_pointers(t_audio *audio)
{
	if (!audio->music || !audio->footstep1 || !audio->footstep2
		|| !audio->door || !audio->button || !audio->plasma_gun
		|| !audio->error || !audio->lift || !audio->bolt_locked
		|| !audio->bolt_unlocked || !audio->plasma_gun_no_ammo
		|| !audio->reload)
		return (true);
	else
		return (false);
}

int	load_game_audio(t_audio *audio)
{
	cleanup_audio_source(audio);
	audio->music = Mix_LoadMUS("audio/eerie_by_eparviai.wav");
	audio->footstep1 = Mix_LoadWAV("audio/footstep1.wav");
	audio->footstep2 = Mix_LoadWAV("audio/footstep2.wav");
	audio->door = Mix_LoadWAV("audio/door_opens_and_closes.wav");
	audio->button = Mix_LoadWAV("audio/button.wav");
	audio->plasma_gun = Mix_LoadWAV("audio/plasma_gun.wav");
	audio->error = Mix_LoadWAV("audio/error.wav");
	load_rahikainen(audio);
	audio->bolt_locked = Mix_LoadWAV("audio/bolt_locked.wav");
	audio->bolt_unlocked = Mix_LoadWAV("audio/bolt_unlocked.wav");
	audio->lift = Mix_LoadWAV("audio/lift.wav");
	audio->plasma_gun_no_ammo = Mix_LoadWAV("audio/out_of_ammo.wav");
	audio->reload = Mix_LoadWAV("audio/reload.wav");
	if (check_invalid_pointers(audio))
	{
		ft_putendl("ERROR: Couldn't load audio.");
		return (1);
	}
	return (0);
}
