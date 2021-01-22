/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:41:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/22 14:13:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void		load_audio(t_audio *audio)
{
	t_audio		audio;
	int			success;

	audio->music = NULL;
	audio->footstep = NULL;
	audio->music = Mix_LoadMUS("../../bluezone.wav");
	if (!audio->music)
		error_output("Failed to load beat music! SDL_mixer Error");
	audio->footstep = Mix_LoadWAV("../../scratch.wav" );
	if (!audio->footstep)
		error_output("Failed to load scratch sound effect!");
}
