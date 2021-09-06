/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_matching_key.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 14:45:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/05 22:16:43 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_bool	matching_key_logic(t_wall *door, int keycard)
{
	if (door->is_locked == cleaning_lock && keycard == keycard_cleaning)
		return (true);
	else if (door->is_locked == engineering_lock
		&& keycard == keycard_engineering)
		return (true);
	else if (door->is_locked == military_lock && keycard == keycard_military)
		return (true);
	else
		return (false);
}

t_bool	check_for_matching_key(t_wall *wall, t_player *plr, int keycard)
{
	if (matching_key_logic(wall, keycard))
	{
		wall->is_locked = unlocked;
		plr->inventory[plr->active_inv].in_use = false;
		plr->active_inv = -1;
		play_sound(plr->audio.unlock_door, 20);
		return (true);
	}
	else if (wall->is_locked == unlocked)
		return (true);
	else
		return (false);
}
