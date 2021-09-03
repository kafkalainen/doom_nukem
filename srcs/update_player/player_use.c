/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_use.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:07:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 09:39:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int		player_use(t_player *plr, t_home *home)
{
	t_xyz			look_dir;
	t_xyz			look_loc;
	t_entity		*entity;
	int				item;

	entity = NULL;
	if (!plr->input.use)
		return (FALSE);
	if (plr->active_inv != -1)
		item = player_use_inventory_item(plr);
	look_dir = vec3_unit_vector(plr->look_dir);
	look_loc = vec3_add(plr->pos, look_dir);
	open_door(home->sectors, look_loc, plr, item);
	entity = activate_object(home, plr);
	if (entity)
	{
		handle_activation(entity, home, plr);
		plr->input.use = 0;
		return (TRUE);
	}
	return (FALSE);
}
