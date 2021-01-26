/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:41:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/26 13:53:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void		load_audio(t_audio *audio)
{
	audio->music = Mix_LoadMUS("srcs/utilities/menacing.wav");
	if (!audio->music)
		error_output("Failed to load beat music! SDL_mixer Error");
	audio->footstep1 = Mix_LoadWAV("srcs/utilities/footstep1.wav" );
	if (!audio->footstep1)
		error_output("Failed to load scratch sound effect!");
	audio->footstep2 = Mix_LoadWAV("srcs/utilities/footstep2.wav" );
	if (!audio->footstep2)
		error_output("Failed to load scratch sound effect!");
}

void		cleanup_audio(t_audio *audio)
{
	Mix_FreeChunk(audio->footstep1);
	audio->footstep1 = NULL;
	Mix_FreeChunk(audio->footstep2);
	audio->footstep2 = NULL;
    Mix_FreeMusic(audio->music);
	audio->music = NULL;
}

void		play_footsteps(t_player *plr)
{
	float			current_time;
	static float	last_time;
	static int		i;

	current_time = SDL_GetTicks();
	if (current_time > last_time + 500)
	{
		if (i)
		{
			Mix_PlayChannel(-1, plr->audio.footstep2, 0);
			i = 0;
		}
		else
		{
			Mix_PlayChannel(-1, plr->audio.footstep1, 0);
			i = 1;
		}
		last_time = current_time;
	}
}
