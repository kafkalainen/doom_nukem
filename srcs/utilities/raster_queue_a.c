/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster_queue_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:44:34 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/24 18:04:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	raster_queue_is_full(t_raster_queue *queue)
{
	return (queue->size == queue->capacity);
}

int	raster_queue_is_empty(t_raster_queue *queue)
{
	return (queue->size == 0);
}

/*
**	Adds an element to the rear-end of the queue.
*/
int	enqueue_to_raster(t_raster_queue *queue, t_triangle *item)
{
	if (queue->rear == queue->capacity - 1)
		return (1);
	if (queue->front == -1)
		queue->front = 0;
	queue->size = queue->size + 1;
	queue->rear = queue->rear + 1;
	queue->array[queue->rear] = *item;
	return (0);
}

/*
**	Removes the first element front-end the queue.
*/
int	dequeue(t_raster_queue *queue)
{
	if (queue->front == -1 || queue->front > queue->rear)
		return (1);
	queue->array[queue->front].hull = false;
	queue->array[queue->front].p[0] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	queue->array[queue->front].p[1] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	queue->array[queue->front].p[2] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	queue->array[queue->front].uv[0] = (t_uvz){0.0f, 0.0f, 0.0f};
	queue->array[queue->front].uv[1] = (t_uvz){0.0f, 0.0f, 0.0f};
	queue->array[queue->front].uv[2] = (t_uvz){0.0f, 0.0f, 0.0f};
	queue->front = queue->front + 1;
	queue->size = queue->size - 1;
	return (0);
}

/*
**	Retrieve first item
*/
int	front(t_raster_queue *queue, t_triangle *triangle)
{
	if (raster_queue_is_empty(queue))
		return (1);
	*triangle = queue->array[queue->front];
	return (0);
}
