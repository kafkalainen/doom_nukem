/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:50:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/07 14:29:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**		Line 31 nulling:
**		might be inefficient
*/
void	*optimized_memcpy(void *pixels, void *src, size_t size)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	s = (char *)src;
	d = (char *)pixels;
	while (i < size)
	{
		d[i] = s[i];
		s[i] = 0;
		i++;
	}
	return (d);
}

/*
** 1st pass at loading char* and converting back to t_texture.
** Need to see text output before making further changes
*/
void	free_array(unsigned char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_strdel((char **)&array[i]);
		i++;
	}
	free(array);
}

t_raster_queue	*create_raster_queue(size_t capacity)
{
	t_raster_queue	*queue;

	queue = (t_raster_queue *)malloc(sizeof(t_raster_queue));
	queue->capacity = capacity;
	queue->front = -1;
	queue->size = 0;
	queue->rear = -1;
	queue->array = (t_triangle *)malloc(queue->capacity * sizeof(t_triangle));
	return (queue);
}

t_raster_queue	*delete_raster_queue(t_raster_queue **queue)
{
	if (!(*queue))
		return (NULL);
	free((*queue)->array);
	free(*queue);
	return (NULL);
}

void	free_queues(t_frame *frame)
{
	unsigned int i;

	i = 0;
	free(frame->depth_buffer);
	delete_raster_queue(&frame->transformed);
	delete_raster_queue(&frame->triangles_in_view);
	while (i < MAX_THREADS)
		delete_raster_queue(&frame->raster_queue[i]);
}
