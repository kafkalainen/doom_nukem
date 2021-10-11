/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pickupable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:10:01 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/11 10:16:22 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	is_pickupable(t_entity *entity)
{
	if (entity->type >= ammo_pack && entity->type <= keycard_military)
		entity->is_pickupable = true;
	else
		entity->is_pickupable = false;
}
