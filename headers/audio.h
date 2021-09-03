/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:35:03 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 09:59:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H

typedef struct s_audio
{
	Mix_Music	*music;
	Mix_Chunk	*footstep1;
	Mix_Chunk	*footstep2;
	Mix_Chunk	*door;
	Mix_Chunk	*button;
	Mix_Chunk	*plasma_gun;
	Mix_Chunk	*error;
	Mix_Chunk	*rahikainen_ramble[3];
	Mix_Chunk	*rahikainen_damage[5];
}				t_audio;

void	cleanup_audio(t_audio *audio);
void	cleanup_audio_source(t_audio *audio);
void	initialize_audio_to_null(t_audio *audio);
int		load_audio(t_audio *audio);
int		load_game_audio(t_audio *audio);
void	play_footsteps(t_audio *audio);
void	play_sound(Mix_Chunk *sound, int volume);

#endif
