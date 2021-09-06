/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster_queue_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:44:33 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 11:29:11 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	add_projectiles(t_home *home, t_frame *frame, t_player *plr)
{
	int				flag;
	Uint32			i;
	t_triangle		bot;
	t_triangle		top;

	i = 0;
	while (i < home->nbr_of_projectiles)
	{
		if (home->projectile_pool[i]->sector_idx == frame->idx)
		{
			top = translate_triangle(&home->projectile_pool[i]->top,
					home->projectile_pool[i]->pos);
			bot = translate_triangle(&home->projectile_pool[i]->bot,
					home->projectile_pool[i]->pos);
			if (enqueue_to_raster(frame->transformed, &top))
				draw_queue_empty(frame, home, plr, &flag);
			if (enqueue_to_raster(frame->transformed, &bot))
				draw_queue_empty(frame, home, plr, &flag);
		}
		if (flag)
			flag = 0;
		else
			i++;
	}
}

t_bool	check_if_entity_is_active(t_entity *entity)
{
	if (entity->is_pickupable && !entity->is_active)
		return (false);
	else
		return (true);
}

void	add_entities(t_home *home, t_frame *frame, t_player *plr)
{
	int				flag;
	Uint32			j;
	t_triangle		tri[2];

	j = 0;
	flag = 0;
	while (j < home->nbr_of_entities)
	{
		if (home->entity_pool[j]->sector_idx == frame->idx
			&& check_if_entity_is_active(home->entity_pool[j]))
		{
			translate_entity(&tri[0], &tri[1], home->entity_pool[j]);
			if (enqueue_to_raster(frame->transformed, &tri[0]))
				draw_queue_empty(frame, home, plr, &flag);
			if (enqueue_to_raster(frame->transformed, &tri[1]))
				draw_queue_empty(frame, home, plr, &flag);
		}
		if (flag)
			flag = 0;
		else
			j++;
	}
}
