/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activate_elevator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:50:13 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/09 14:13:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	activate_elevator(t_home *home, t_entity *entity, t_player *plr)
{
	if (entity->is_linked > 1)
	{
		if (home->sectors[entity->is_linked - 2]->moving_until < plr->time)
		{
			home->sectors[entity->is_linked - 2]->moving_until =
				plr->time + 10000;
			if (entity->state)
				home->sectors[entity->is_linked - 2]->elevator_dir = '+';
			else
				home->sectors[entity->is_linked - 2]->elevator_dir = '-';
		}
	}
}
