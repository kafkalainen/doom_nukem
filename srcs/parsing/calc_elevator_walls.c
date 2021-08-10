/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_elevator_walls.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:02:11 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/10 16:32:20 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_extra_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:05:11 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/10 14:00:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	calc_elevator_walls(t_home *home)
{
	Uint32	i;
	Uint32	j;
	t_wall	*current_portal;
	t_wall	*portal_behind;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		j = 0;
		current_portal = home->sectors[i]->walls;
		while (home->sectors[i]->is_elevator
			&& j < home->sectors[i]->nb_of_walls)
		{
			if (current_portal->top.idx >= 0 && !current_portal->is_door
				&& home->sectors[current_portal->top.idx]->is_elevator)
			{

				portal_behind = get_portal_by_idx(i,
						home->sectors[current_portal->top.idx]);

				current_portal->is_door = 1;
				portal_behind->is_door = 1;
				home->sectors[i]->nb_of_walls += generate_doors(current_portal);
				home->sectors[current_portal->top.idx]->nb_of_walls
					+= generate_doors(portal_behind);
			}
			current_portal = current_portal->next;
			j++;
		}
		i++;
	}
}
