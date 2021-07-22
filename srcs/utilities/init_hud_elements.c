/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:21:40 by tmaarela          #+#    #+#             */
/*   Updated: 2021/07/21 14:02:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int		initialize_hud(t_hud *hud)
{
	hud->idx[0] = -1;
	hud->idx[1] = -1;
	hud->hud_hp_x = 58.0f;
	hud->hud_hp_y = 562.0f;
	hud->hud_ammo_x = 630.0f;
	hud->hud_ammo_y = 570.0f;
	hud->hud_fuel_x = 58.0f;
	hud->hud_fuel_y = 525.0f;
	return (0);
}
