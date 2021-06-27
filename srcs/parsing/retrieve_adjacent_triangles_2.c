/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_adjacent_triangles_2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 13:04:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/27 13:14:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	retrieve_adjacent_wall_triangles(t_triangle *tri, t_sector *sector,
		t_raster_queue *queue, Uint32 current_point)
{
	Uint32			i;
	t_wall			*walls;

	i = 0;
	walls = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (check_if_same_point(tri->p[current_point], walls->top.p[0]))
			enqueue_to_raster(queue, &walls->top);
		if (check_if_same_point(tri->p[current_point], walls->top.p[1]))
			enqueue_to_raster(queue, &walls->top);
		if (check_if_same_point(tri->p[current_point], walls->top.p[2]))
			enqueue_to_raster(queue, &walls->top);
		if (check_if_same_point(tri->p[current_point], walls->bottom.p[0]))
			enqueue_to_raster(queue, &walls->bottom);
		if (check_if_same_point(tri->p[current_point], walls->bottom.p[1]))
			enqueue_to_raster(queue, &walls->bottom);
		if (check_if_same_point(tri->p[current_point], walls->bottom.p[2]))
			enqueue_to_raster(queue, &walls->bottom);
		walls = walls->next;
		i++;
	}
}

void	ceiling_retrieve_adjacent_triangles_ceiling(t_surface *surf, t_sector *sector,
		t_raster_queue *queue, Uint32 current_point)
{
	Uint32		i;
	t_surface	*ceiling;

	i = 0;
	ceiling = surf->next;
	while (i < sector->nb_of_ceil - 1)
	{
		if (check_if_same_point(surf->tri.p[current_point], ceiling->tri.p[0]))
			enqueue_to_raster(queue, &ceiling->tri);
		if (check_if_same_point(surf->tri.p[current_point], ceiling->tri.p[1]))
			enqueue_to_raster(queue, &ceiling->tri);
		if (check_if_same_point(surf->tri.p[current_point], ceiling->tri.p[2]))
			enqueue_to_raster(queue, &ceiling->tri);
		ceiling = ceiling->next;
		i++;
	}
}

void	ground_retrieve_adjacent_triangles_ground(t_surface *surf, t_sector *sector,
		t_raster_queue *queue, Uint32 current_point)
{
	Uint32		i;
	t_surface	*ground;

	i = 0;
	ground = surf->next;
	while (i < sector->nb_of_ground - 1)
	{
		if (check_if_same_point(surf->tri.p[current_point], ground->tri.p[0]))
			enqueue_to_raster(queue, &ground->tri);
		if (check_if_same_point(surf->tri.p[current_point], ground->tri.p[1]))
			enqueue_to_raster(queue, &ground->tri);
		if (check_if_same_point(surf->tri.p[current_point], ground->tri.p[2]))
			enqueue_to_raster(queue, &ground->tri);
		ground = ground->next;
		i++;
	}
}
