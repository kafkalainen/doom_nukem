/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 14:34:05 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/07 12:35:44 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	play_footsteps(t_audio *audio)
{
	Uint32			current_time;
	static Uint32	last_time;
	static int		step;

	current_time = SDL_GetTicks();
	if (current_time > last_time + 600)
	{
		if (step)
		{
			Mix_PlayChannel(-1, audio->footstep1, 0);
			step = 0;
		}
		else
		{
			Mix_PlayChannel(-1, audio->footstep2, 0);
			step = 1;
		}
		last_time = current_time;
	}
}

void	play_sound(Mix_Chunk *sound, int volume)
{
	if (!sound)
		return ;
	Mix_VolumeChunk(sound, volume);
	Mix_PlayChannel(-1, sound, 0);
}

void	toggle_music(Mix_Music *music)
{
	if (!Mix_PlayingMusic())
	{
		Mix_PlayMusic(music, -1);
		Mix_VolumeMusic(30);
	}
	else if (Mix_PausedMusic())
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
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
