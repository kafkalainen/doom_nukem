/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:41:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 11:25:32 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	free_sound(Mix_Chunk **chunk)
{
	if (*chunk != NULL)
		Mix_FreeChunk(*chunk);
	*chunk = NULL;
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
	free_sound(&audio->rahikainen_damage[0]);
	free_sound(&audio->rahikainen_damage[1]);
	free_sound(&audio->rahikainen_damage[2]);
	free_sound(&audio->rahikainen_damage[3]);
	free_sound(&audio->rahikainen_damage[4]);
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
	audio->rahikainen_ramble[0] = Mix_LoadWAV("audio/rahikainen_1.wav");
	audio->rahikainen_ramble[1] = Mix_LoadWAV("audio/rahikainen_2.wav");
	audio->rahikainen_ramble[2] = Mix_LoadWAV("audio/rahikainen_3.wav");
	audio->rahikainen_damage[0] = Mix_LoadWAV("audio/rahikainen_aah_1.wav");
	audio->rahikainen_damage[1] = Mix_LoadWAV("audio/rahikainen_damage.wav");
	audio->rahikainen_damage[2] = Mix_LoadWAV("audio/rahikainen_ugh.wav");
	audio->rahikainen_damage[3] = Mix_LoadWAV("audio/rahikainen_ugh_2.wav");
	audio->rahikainen_damage[4] = Mix_LoadWAV("audio/rahikainen_ugh_3.wav");
	audio->error = Mix_LoadWAV("audio/error.wav");
	if (!audio->music || !audio->footstep1 || !audio->footstep2
		|| !audio->door || !audio->button || !audio->plasma_gun
		|| !audio->error)
	{
		ft_putendl("ERROR: Couldn't load audio.");
		return (1);
	}
	return (0);
}

int	load_audio(t_audio *audio)
{
	audio->music = Mix_LoadMUS("audio/eerie_by_eparviai.wav");
	if (!audio->music)
	{
		ft_putendl_fd("Failed to load beat music! SDL_mixer Error", 2);
		audio->footstep1 = NULL;
		audio->footstep2 = NULL;
		return (771);
	}
	audio->footstep1 = Mix_LoadWAV("audio/footstep1.wav");
	if (!audio->footstep1)
	{
		ft_putendl_fd("Failed to load scratch sound effect!", 2);
		audio->footstep2 = NULL;
		return (772);
	}
	audio->footstep2 = Mix_LoadWAV("audio/footstep2.wav");
	if (!audio->footstep2)
	{
		ft_putendl_fd("Failed to load scratch sound effect!", 2);
		return (773);
	}
	return (0);
}

/*
**	Should FreeWAV(t_chunk*) be used here?
*/

void	cleanup_audio(t_audio *audio)
{
	if (audio->footstep1 != NULL)
	{
		Mix_FreeChunk(audio->footstep1);
		audio->footstep1 = NULL;
	}
	if (audio->footstep2 != NULL)
	{
		Mix_FreeChunk(audio->footstep2);
		audio->footstep2 = NULL;
	}
	if (audio->music != NULL)
	{
		Mix_FreeMusic(audio->music);
		audio->music = NULL;
	}
	Mix_CloseAudio();
}
