/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_use.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:07:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/22 10:24:34 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int		player_use(t_player *plr, t_home *home, Uint32 delta_time)
{
	t_xyz			look_dir;
	t_xyz			look_loc;
	// Uint32			doors_closing;

	close_doors(home->sectors, home->nbr_of_sectors, plr->time, delta_time);
	// doors_closing = close_doors(home->sectors, home->nbr_of_sectors, plr->time, delta_time);
	// if (doors_closing)
	// 	play_sound(plr->audio.door_closing);
	if (!plr->input.use)
		return (FALSE);
	look_dir = vec3_unit_vector(plr->look_dir);
	look_loc = vec3_add(plr->pos, look_dir);
	if (open_door(home->sectors, look_loc, plr->time, plr->cur_sector))
		return (TRUE);
	// 	play_sound(plr->audio.door_opening);
	return (TRUE);
}
