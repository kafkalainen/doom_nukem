/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:35:03 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/22 09:45:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H

typedef struct s_audio
{
	Mix_Music	*music;
	Mix_Chunk	*battery_low;
	Mix_Chunk	*bolt_unlocked;
	Mix_Chunk	*bolt_locked;
	Mix_Chunk	*button;
	Mix_Chunk	*door;
	Mix_Chunk	*error;
	Mix_Chunk	*footstep1;
	Mix_Chunk	*footstep2;
	Mix_Chunk	*lift;
	Mix_Chunk	*plasma_gun;
	Mix_Chunk	*plasma_gun_no_ammo;
	Mix_Chunk	*power_station_depleted;
	Mix_Chunk	*rahikainen_die;
	Mix_Chunk	*rahikainen_ramble[4];
	Mix_Chunk	*rahikainen_damage[5];
	Mix_Chunk	*reload;
	Mix_Chunk	*recharge;
	Mix_Chunk	*skull_skulker_aggro;
	Mix_Chunk	*skull_skulker_attack;
	Mix_Chunk	*skull_skulker_damage;
	Mix_Chunk	*skull_skulker_death;
	Mix_Chunk	*thing_aggro;
	Mix_Chunk	*thing_attack;
	Mix_Chunk	*thing_damage;
	Mix_Chunk	*thing_death;
	Mix_Chunk	*typing;
	Mix_Chunk	*unlock_door;
}				t_audio;

typedef struct s_audio_asset
{
	unsigned int	size;
	t_uchar			*buf;
}				t_audio_asset;

void	cleanup_audio(t_audio *audio);
void	cleanup_audio_source(t_audio *audio);
void	initialize_audio_to_null(t_audio *audio);
int		load_audio(t_audio *audio);
int		load_game_audio(t_audio *audio);
void	play_footsteps(t_audio *audio);
int		play_sound(Mix_Chunk *sound, int volume);
void	toggle_music(Mix_Music *music);
int		play_sound_and_fadeout(Mix_Chunk *sound, int volume, Uint32 playtime);

#endif
