/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster_queue_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 12:13:33 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/07 13:48:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	quick_reset_queue(t_raster_queue *queue)
{
	queue->front = -1;
	queue->rear = -1;
	queue->size = 0;
}

void	draw_queue_empty(t_frame *frame, t_home *home, t_player *plr,
		int *flag)
{
	draw_sector(frame, home, plr, frame->idx);
	quick_reset_queue(frame->transformed);
	*flag = 1;
}

void	add_ground(t_home *home, t_frame *frame, t_player *plr)
{
	Uint32			j;
	int				flag;
	t_surface		*ground;

	j = 0;
	ground = home->sectors[frame->idx]->ground;
	while (j < home->sectors[frame->idx]->nb_of_ground)
	{
		if (enqueue_to_raster(frame->transformed, &ground->tri))
			draw_queue_empty(frame, home, plr, &flag);
		if (flag)
			flag = 0;
		else
		{
			ground = ground->next;
			j++;
		}
	}
}

void	add_ceiling(t_home *home, t_frame *frame, t_player *plr)
{
	Uint32			j;
	int				flag;
	t_surface		*ceiling;

	j = 0;
	ceiling = home->sectors[frame->idx]->ceiling;
	while (j < home->sectors[frame->idx]->nb_of_ceil)
	{
		if (enqueue_to_raster(frame->transformed, &ceiling->tri))
			draw_queue_empty(frame, home, plr, &flag);
		if (flag)
			flag = 0;
		else
		{
			ceiling = ceiling->next;
			j++;
		}
	}
}

void	add_walls(t_home *home, t_frame *frame, t_player *plr)
{
	Uint32		i;
	int			flag;
	t_wall		*wall;

	i = 0;
	flag = 0;
	wall = home->sectors[frame->idx]->walls;
	while (i < home->sectors[frame->idx]->nb_of_walls * 2)
	{
		if (wall->top.idx < 0)
		{
			if (enqueue_to_raster(frame->transformed, &wall->top))
				draw_queue_empty(frame, home, plr, &flag);
			if (enqueue_to_raster(frame->transformed, &wall->bottom))
				draw_queue_empty(frame, home, plr, &flag);
		}
		if (flag)
			flag = 0;
		else
		{
			wall = wall->next;
			i++;
		}
	}
}
