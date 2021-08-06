/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update_movement.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:29:25 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/06 13:37:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"


Uint32	update_player_to_new_location(t_player *plr, t_wall *wall,
	t_sector **sector, Uint32 time)
{
	plr->cur_sector = wall->top.idx;
	if (sector[plr->cur_sector]->lights.is_linked == 1)
		sector[plr->cur_sector]->lights.state = TRUE;
	plr->pos = vec3_add(plr->pos, vec3_mul(plr->move_dir, time * 0.005f));
	return (TRUE);
}
