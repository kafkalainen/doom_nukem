/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_all_audio_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 13:40:09 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 17:18:42 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	parse_rahikainen(unsigned char *buf, unsigned int *pos,
			ssize_t size)
{
	parse_audio_data(buf, pos, "./temp/rahikainen_1.wav", size);
	parse_audio_data(buf, pos, "./temp/rahikainen_2.wav", size);
	parse_audio_data(buf, pos, "./temp/rahikainen_3.wav", size);
	parse_audio_data(buf, pos, "./temp/rahikainen_4.wav", size);
	parse_audio_data(buf, pos, "./temp/rahikainen_aah_1.wav", size);
	parse_audio_data(buf, pos, "./temp/rahikainen_ugh.wav", size);
	parse_audio_data(buf, pos, "./temp/rahikainen_ugh_2.wav", size);
	parse_audio_data(buf, pos, "./temp/rahikainen_ugh_3.wav", size);
	parse_audio_data(buf, pos, "./temp/rahikainen_damage.wav", size);
	parse_audio_data(buf, pos, "./temp/rahikainen_die.wav", size);
	parse_audio_data(buf, pos, "./temp/rahikainen_hits.wav", size);
	parse_audio_data(buf, pos, "./temp/typing.wav", size);
}

static void	parse_enemy(unsigned char *buf, unsigned int *pos,
			ssize_t size)
{
	parse_audio_data(buf, pos, "./temp/skull_skulker_lulling.wav", size);
	parse_audio_data(buf, pos, "./temp/skull_skulker_aggro.wav", size);
	parse_audio_data(buf, pos, "./temp/skull_skulker_attack.wav", size);
	parse_audio_data(buf, pos, "./temp/skull_skulker_damage.wav", size);
	parse_audio_data(buf, pos, "./temp/skull_skulker_death.wav", size);
	parse_audio_data(buf, pos, "./temp/thing_lulling.wav", size);
	parse_audio_data(buf, pos, "./temp/thing_aggro.wav", size);
	parse_audio_data(buf, pos, "./temp/thing_attack.wav", size);
	parse_audio_data(buf, pos, "./temp/thing_damage.wav", size);
	parse_audio_data(buf, pos, "./temp/thing_die.wav", size);
}

static void	parse_plr_action_sounds(unsigned char *buf, unsigned int *pos,
			ssize_t size)
{
	parse_audio_data(buf, pos, "./temp/footstep1.wav", size);
	parse_audio_data(buf, pos, "./temp/footstep2.wav", size);
	parse_audio_data(buf, pos, "./temp/door_opens_and_closes.wav", size);
	parse_audio_data(buf, pos, "./temp/button.wav", size);
	parse_audio_data(buf, pos, "./temp/plasma_gun.wav", size);
	parse_audio_data(buf, pos, "./temp/error.wav", size);
}

int	parse_all_audio_data(unsigned char *buf, ssize_t size)
{
	unsigned int	pos;

	pos = 0;
	buf = (unsigned char *)ft_memstr((char *)buf, "doom_music #", size);
	pos += get_next_breaker(buf + pos);
	if (pos > (unsigned int)size)
		error_output("Pointer points outside memory address\n");
	parse_audio_data(buf, &pos, "./temp/eerie_by_eparviai.wav", size);
	parse_plr_action_sounds(buf, &pos, size);
	parse_rahikainen(buf, &pos, size);
	parse_enemy(buf, &pos, size);
	parse_audio_data(buf, &pos, "./temp/bolt_locked.wav", size);
	parse_audio_data(buf, &pos, "./temp/bolt_unlocked.wav", size);
	parse_audio_data(buf, &pos, "./temp/lift.wav", size);
	parse_audio_data(buf, &pos, "./temp/out_of_ammo.wav", size);
	parse_audio_data(buf, &pos, "./temp/reload.wav", size);
	parse_audio_data(buf, &pos, "./temp/door_unlocked.wav", size);
	parse_audio_data(buf, &pos, "./temp/power_station_depleted.wav", size);
	parse_audio_data(buf, &pos, "./temp/battery_low.wav", size);
	parse_audio_data(buf, &pos, "./temp/charging_suit.wav", size);
	return (0);
}
