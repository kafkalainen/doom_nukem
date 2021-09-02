/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_matching_key.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 14:45:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/02 15:13:44 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_for_matching_key(t_wall *wall, t_player *plr, int keycard)
{

	if (wall->is_locked == cleaning_lock && keycard == keycard_cleaning)
	{
		wall->is_locked = unlocked;
		plr->inventory[plr->active_inv].in_use = false;
		plr->active_inv = -1;
		return (true);
	}
	else if (wall->is_locked == engineering_lock && keycard == keycard_engineering)
	{
		wall->is_locked = unlocked;
		plr->inventory[plr->active_inv].in_use = false;
		return (true);
	}
	else if (wall->is_locked == military_lock && keycard == keycard_military)
	{
		wall->is_locked = unlocked;
		plr->inventory[plr->active_inv].in_use = false;
		return (true);
	}
	else if (wall->is_locked == unlocked)
		return (true);
	else
		return (false);
}
