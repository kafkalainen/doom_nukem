/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_use_inventory_item.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:52:21 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/02 14:16:30 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	player_use_inventory_item(t_player *plr)
{
	if (plr->inventory[plr->active_inv].in_use)
	{
		if (plr->inventory[plr->active_inv].sprite_idx == ammo_pack_sprite)
			plr->wep->ammo += 10;
		else if (plr->inventory[plr->active_inv].sprite_idx
			== military_keycard_sprite)
			return (keycard_military);
		else if (plr->inventory[plr->active_inv].sprite_idx
			== cleaning_keycard_sprite)
			return (keycard_cleaning);
		else if (plr->inventory[plr->active_inv].sprite_idx
			== engineering_keycard_sprite)
			return (keycard_engineering);
		plr->inventory[plr->active_inv].in_use = false;
		plr->active_inv = -1;
	}
	return (0);
}
