/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_functions_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 14:33:32 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/07 14:48:24 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	initialize_rasterization_queues(t_frame *frame)
{
	unsigned int i;

	i = 0;
	frame->transformed = create_raster_queue(100); //DEALLOCATE
	if (!frame->transformed)
		return (1);
	frame->triangles_in_view = create_raster_queue(100); //DEALLOCATE
	if (!frame->triangles_in_view)
		return (1);
	frame->raster_queue = (t_raster_queue**)malloc(sizeof(t_raster_queue*) * (MAX_THREADS + 1));
	if (!frame->raster_queue)
		return (1);
	while (i < MAX_THREADS)
	{
		frame->raster_queue[i] = create_raster_queue(200); //DEALLOCATE
		if (!frame->raster_queue)
			return (1);
		i++;
	}
	frame->depth_buffer = (float *)malloc(sizeof(float)
			* (float)SCREEN_WIDTH * (float)SCREEN_HEIGHT);
	if (!frame->depth_buffer)
		return (1);
	return (0);
}
