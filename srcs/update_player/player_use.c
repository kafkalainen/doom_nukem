/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_use.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:07:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/06 20:40:24 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	player_use(t_player *plr, t_home *home)
{
	t_entity		*entity;
	int				item;

	entity = NULL;
	if (!plr->input.use)
		return (FALSE);
	if (plr->active_inv != -1)
		item = player_use_inventory_item(plr);
	else
		item = 0;
	open_door(home->sectors, plr, item);
	entity = activate_object(home, plr);
	if (entity)
	{
		handle_activation(entity, home, plr);
		plr->input.use = 0;
		return (TRUE);
	}
	return (FALSE);
}
