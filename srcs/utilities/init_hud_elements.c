/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:21:40 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/03 11:09:47 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int		initialize_hud(t_hud *hud)
{
	if (!hud)
		return (1);
	hud->idx[0] = -1;
	hud->idx[1] = -1;
	hud->hud_hp_x = 58.0f;
	hud->hud_hp_y = 562.0f;
	hud->hud_ammo_x = 630.0f;
	hud->hud_ammo_y = 570.0f;
	hud->hud_fuel_x = 58.0f;
	hud->hud_fuel_y = 525.0f;
	hud->vm_x = 530.0f;
	hud->vm_y = 280.0f;
	hud->vm_mx = 0.0f;
	hud->vm_my = 0.0f;
	hud->vm_rx = 0.0f;
	hud->vm_ry = 0.0f;
	return (0);
}
