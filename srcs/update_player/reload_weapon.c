/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 21:45:34 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 10:26:37 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	reload_weapon(t_player *plr, Uint32 t)
{
	if (plr->reload > 0)
	{
		plr->reload -= t;
		if (plr->reload <= 0)
		{
			plr->wep[plr->active_wep].ammo += 10;
		}
	}
}
