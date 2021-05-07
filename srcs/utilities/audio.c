/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:41:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/07 12:24:01 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void		clean_up_audio_source(t_audio *audio)
{
	if (audio->footstep1 != NULL)
		Mix_FreeChunk(audio->footstep1);
	audio->footstep1 = NULL;
	if (audio->footstep2 != NULL)
		Mix_FreeChunk(audio->footstep2);
	audio->footstep2 = NULL;
	if (audio->music != NULL)
		Mix_FreeMusic(audio->music);
	audio->music = NULL;
}

int			load_game_audio(t_audio *audio)
{
	clean_up_audio_source(audio);
	audio->music = Mix_LoadMUS("temp/music.wav");
	if (!audio->music)
	{
		ft_putendl_fd("Failed to load beat music! SDL_mixer Error", 2);
		audio->footstep1 = NULL;
		audio->footstep2 = NULL;
		return (771);
	}
	audio->footstep1 = Mix_LoadWAV("temp/footstep1.wav");
	if (!audio->footstep1)
	{
		ft_putendl_fd("Failed to load scratch sound effect!", 2);
		audio->footstep2 = NULL;
		return (772);
	}
	audio->footstep2 = Mix_LoadWAV("temp/footstep2.wav");
	if (!audio->footstep2)
	{
		ft_putendl_fd("Failed to load scratch sound effect!", 2);
		return (773);
	}
	return (0);
}

int			load_audio(t_audio *audio)
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

void		cleanup_audio(t_audio *audio)
{
	Mix_FreeChunk(audio->footstep1);
	audio->footstep1 = NULL;
	Mix_FreeChunk(audio->footstep2);
	audio->footstep2 = NULL;
	Mix_FreeMusic(audio->music);
	audio->music = NULL;
	Mix_CloseAudio();
}

void		play_footsteps(t_player *plr)
{
	Uint32			current_time;
	static Uint32	last_time;
	static int		step;

	current_time = SDL_GetTicks();
	if (current_time > last_time + 600)
	{
		if (step)
		{
			Mix_PlayChannel(-1, plr->audio.footstep1, 0);
			step = 0;
		}
		else
		{
			Mix_PlayChannel(-1, plr->audio.footstep2, 0);
			step = 1;
		}
		last_time = current_time;
	}
}
