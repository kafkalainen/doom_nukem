/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster_queue_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:44:33 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/07 15:10:10 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// j = 0;
// while (j < home->nbr_of_projectiles)
// {
// 	if (home->projectile_pool[j]->sector_idx == idx)
// 	{
// 		transformed->array[transformed->size]
//		= translate_triangle(&home->projectile_pool[j]->top,
//		home->entity_pool[j]->coordinates);
// 		transformed->size += 1;
// 		transformed->array[transformed->size]
//		= translate_triangle(&home->projectile_pool[j]->bot,
//		home->entity_pool[j]->coordinates);
// 		transformed->size += 1;
// 	}
// 	j++;
// }
void	add_objects(t_home *home, t_frame *frame, t_player *plr)
{
	int				flag;
	Uint32			j;
	t_triangle		bot;
	t_triangle		top;

	j = 0;
	flag = 0;
	while (j < home->nbr_of_entities)
	{
		if (home->entity_pool[j]->sector_idx == frame->idx)
		{
			top = translate_triangle(&home->entity_pool[j]->top,
					home->entity_pool[j]->pos);
			bot = translate_triangle(&home->entity_pool[j]->bot,
					home->entity_pool[j]->pos);
			if (enqueue_to_raster(frame->transformed, &top))
				draw_queue_empty(frame, home, plr, &flag);
			if (enqueue_to_raster(frame->transformed, &bot))
				draw_queue_empty(frame, home, plr, &flag);
		}
		if (flag)
			flag = 0;
		else
			j++;
	}
}
