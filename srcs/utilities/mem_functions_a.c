/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_functions_a.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:50:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/07 14:43:56 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

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
	if (!queue)
		return (queue);
	queue->capacity = capacity;
	queue->front = -1;
	queue->size = 0;
	queue->rear = -1;
	queue->array = (t_triangle *)malloc(queue->capacity * sizeof(t_triangle));
	if (!queue->array)
		error_output("Memory allocation of raster array failed\n");
	return (queue);
}

t_raster_queue	*delete_raster_queue(t_raster_queue **queue)
{
	if (!queue)
		return (NULL);
	if (!(*queue))
		return (NULL);
	free((*queue)->array);
	free(*queue);
	return (NULL);
}

void	free_queues(t_frame *frame)
{
	unsigned int	i;

	i = 0;
	if (!frame)
		return ;
	frame->transformed = delete_raster_queue(&frame->transformed);
	frame->triangles_in_view = delete_raster_queue(&frame->triangles_in_view);
	if (frame->raster_queue)
	{
		while (i < MAX_THREADS)
		{
			free(frame->raster_queue[i]->array);
			free(frame->raster_queue[i]);
			i++;
		}
		free(frame->raster_queue);
	}
	if (frame->depth_buffer)
		free(frame->depth_buffer);
	frame->depth_buffer = NULL;
	if (frame->viewport.mid_planes)
		free(frame->viewport.mid_planes);
	frame->viewport.mid_planes = NULL;
}
