/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_twist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:09:41 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/06 12:59:43 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	plot_twist(t_home *home, t_player *plr)
{
	t_uint		i;

	i = 0;
	(void)plr;
	while (i < home->nbr_of_entities)
	{
		if (is_enemy(home->entity_pool[i]->type))
		{
			home->entity_pool[i]->is_revealed = true;
			initialize_triangle_index(&home->entity_pool[i]->top,
				home->entity_pool[i]);
			initialize_triangle_index(&home->entity_pool[i]->bot,
				home->entity_pool[i]);
		}
		i++;
	}
}
