/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:41:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/25 12:34:45 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void		load_audio(t_audio *audio)
{
	audio->music = Mix_LoadMUS("srcs/utilities/menacing.wav");
	if (!audio->music)
		//error_output("Failed to load beat music! SDL_mixer Error");
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
//	audio->footstep = Mix_LoadWAV("../../scratch.wav" );
//	if (!audio->footstep)
//		error_output("Failed to load scratch sound effect!");
}
