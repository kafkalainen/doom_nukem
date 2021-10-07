/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 14:34:05 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/07 14:38:51 by rzukale          ###   ########.fr       */
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
			play_sound(audio->footstep1, 30);
			step = 0;
		}
		else
		{
			play_sound(audio->footstep2, 30);
			step = 1;
		}
		last_time = current_time;
	}
}

int	play_sound(Mix_Chunk *sound, int volume)
{
	int	channel;

	if (!sound)
		return (-1);
	channel = Mix_PlayChannel(-1, sound, 0);
	channel = Mix_Volume(channel, volume);
	return (channel);
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
