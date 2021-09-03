/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 14:34:05 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 20:24:01 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	initialize_audio_to_null(t_audio *audio)
{
	audio->footstep1 = NULL;
	audio->footstep2 = NULL;
	audio->music = NULL;
	audio->door = NULL;
	audio->button = NULL;
	audio->plasma_gun = NULL;
	audio->error = NULL;
	audio->rahikainen_ramble[0] = NULL;
	audio->rahikainen_ramble[1] = NULL;
	audio->rahikainen_ramble[2] = NULL;
	audio->rahikainen_damage[0] = NULL;
	audio->rahikainen_damage[1] = NULL;
	audio->rahikainen_damage[2] = NULL;
	audio->rahikainen_damage[3] = NULL;
	audio->rahikainen_damage[4] = NULL;
	audio->bolt_unlocked = NULL;
	audio->bolt_locked = NULL;
	audio->lift = NULL;
}

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
