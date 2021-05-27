/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:44:34 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/27 20:01:31 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int raster_queue_is_full(t_raster_queue *queue)
{
	return (queue->size == queue->capacity);
}

int	raster_queue_is_empty(t_raster_queue *queue)
{
	return (queue->size == 0);
}


/*
**	Add to queue
*/
int	enqueue_to_raster(t_raster_queue *queue, t_triangle item)
{
	if (raster_queue_is_full(queue))
		return (1);
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = item;
	queue->size = queue->size + 1;
	return (0);
}

/*
**	Remove from queue
*/
int	dequeue(t_raster_queue *queue)
{
	if (raster_queue_is_empty(queue))
		return (1);
	//item = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size = queue->size - 1;
	return (0);
}

/*
**	Retrieve first item
*/
int front(t_raster_queue *queue, t_triangle *triangle)
{
	if (raster_queue_is_empty(queue))
		return (1);
	*triangle = queue->array[queue->front];
	return (0);
}
