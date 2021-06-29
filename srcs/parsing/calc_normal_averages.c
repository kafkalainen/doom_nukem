/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_normal_averages.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 13:18:01 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/29 11:08:47 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	calc_top_normal_averages(t_sector *sector, t_raster_queue *queue)
{
	Uint32	i;
	Uint32	j;
	t_wall	*current;

	i = 0;
	current = sector->walls;
	while (i < sector->nb_of_walls)
	{
		j = 0;
		while (j < 3)
		{
			queue->front = -1;
			queue->rear = -1;
			queue->size = 0;
			retrieve_adjacent_triangles_ceiling(&current->top, sector, queue, j);
			retrieve_adjacent_triangles_ground(&current->top, sector, queue, j);
			retrieve_adjacent_top_triangles_walls(current, sector, queue, j);
			current->top.vertex_normal[j] = vec3_calc_vector_average(queue);
			j++;
		}
		current = current->next;
		i++;
	}
}

void	calc_bottom_normal_averages(t_sector *sector, t_raster_queue *queue)
{
	Uint32	i;
	Uint32	j;
	t_wall	*current;

	i = 0;
	current = sector->walls;
	while (i < sector->nb_of_walls)
	{
		j = 0;
		while (j < 3)
		{
			queue->front = -1;
			queue->rear = -1;
			queue->size = 0;
			retrieve_adjacent_triangles_ceiling(&current->bottom, sector, queue, j);
			retrieve_adjacent_triangles_ground(&current->bottom, sector, queue, j);
			retrieve_adjacent_bottom_triangles_walls(current, sector, queue, j);
			current->bottom.vertex_normal[j] = vec3_calc_vector_average(queue);
			j++;
		}
		current = current->next;
		i++;
	}
}

void	calc_ceiling_normal_averages(t_sector *sector, t_raster_queue *queue)
{
	Uint32		i;
	Uint32		j;
	t_surface	*current;

	i = 0;
	current = sector->ceiling;
	while (i < sector->nb_of_ceil)
	{
		j = 0;
		while (j < 3)
		{
			queue->front = -1;
			queue->rear = -1;
			queue->size = 0;
			retrieve_adjacent_wall_triangles(&current->tri, sector, queue, j);
			retrieve_adjacent_triangles_ground(&current->tri, sector, queue, j);
			ceiling_retrieve_adjacent_triangles_ceiling(current, sector, queue, j);
			current->tri.vertex_normal[j] = vec3_calc_vector_average(queue);
			j++;
		}
		current = current->next;
		i++;
	}
}

void	calc_ground_normal_averages(t_sector *sector, t_raster_queue *queue)
{
	Uint32		i;
	Uint32		j;
	t_surface	*current;

	i = 0;
	current = sector->ground;
	while (i < sector->nb_of_ground)
	{
		j = 0;
		while (j < 3)
		{
			queue->front = -1;
			queue->rear = -1;
			queue->size = 0;
			retrieve_adjacent_wall_triangles(&current->tri, sector, queue, j);
			retrieve_adjacent_triangles_ceiling(&current->tri, sector, queue, j);
			ground_retrieve_adjacent_triangles_ground(current, sector, queue, j);
			current->tri.vertex_normal[j] = vec3_calc_vector_average(queue);
			j++;
		}
		current = current->next;
		i++;
	}
}
