/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_use_inventory_item.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:52:21 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 10:07:29 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	player_use_inventory_item(t_player *plr)
{
	if (plr->inventory[plr->active_inv].in_use)
	{
		if (plr->inventory[plr->active_inv].sprite_idx == ammo_pack_sprite
			&& plr->reload <= 0)
		{
			plr->reload = 3000;
			plr->inventory[plr->active_inv].in_use = false;
			plr->active_inv = -1;
			play_sound(plr->audio.reload, 30);
		}
		else if (plr->inventory[plr->active_inv].sprite_idx
			== military_keycard_sprite)
			return (keycard_military);
		else if (plr->inventory[plr->active_inv].sprite_idx
			== cleaning_keycard_sprite)
			return (keycard_cleaning);
		else if (plr->inventory[plr->active_inv].sprite_idx
			== engineering_keycard_sprite)
			return (keycard_engineering);
	}
	return (0);
}
