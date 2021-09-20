/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_functions_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 14:33:32 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/18 08:56:11 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	initialize_midplanes(t_sides *viewport)
{
	Uint32	i;
	Uint32	span;

	i = 0;
	span = (SCREEN_HEIGHT) / MAX_THREADS;
	while (i < MAX_THREADS)
	{
		viewport->mid_planes[i]
			= (t_plane){(t_xyz){0.0f, span * i, 0.0f, 1.0f},
			(t_xyz){0.0f, 1.0f, 0.0f, 0.0f}};
		i++;
	}
	viewport->mid_planes[i]
		= (t_plane){(t_xyz){0.0f, SCREEN_HEIGHT, 0.0f, 1.0f},
		(t_xyz){0.0f, 1.0f, 0.0f, 0.0f}};
}

static int	initialize_viewport(t_sides *viewport)
{
	viewport->mid_planes = (t_plane *)malloc(sizeof(t_plane)
			* (MAX_THREADS + 1));
	if (!(viewport->mid_planes))
		return (1);
	viewport->top = (t_plane){(t_xyz){0.0f, 0.0f, 0.0f, 1.0f},
		(t_xyz){0.0f, 1.0f, 0.0f, 0.0f}};
	viewport->bottom = (t_plane){(t_xyz){0.0f, SCREEN_HEIGHT - 1, 0.0f, 1.0f},
		(t_xyz){0.0f, -1.0f, 0.0f, 0.0f}};
	viewport->left = (t_plane){(t_xyz){0.0f, 0.0f, 0.0f, 1.0f},
		(t_xyz){1.0f, 0.0f, 0.0f, 0.0f}};
	viewport->right = (t_plane){(t_xyz){SCREEN_WIDTH - 1.0f, 0.0f, 0.0f, 1.0f},
		(t_xyz){-1.0f, 0.0f, 0.0f, 0.0f}};
	viewport->near = (t_plane){(t_xyz){0.0f, 0.0f, 0.1f, 1.0f},
		(t_xyz){0.0f, 0.0f, 1.0f, 0.0f}};
	viewport->view_offset = (t_xyz){1.0f, 1.0f, 0.0f, 1.0f};
	initialize_midplanes(viewport);
	return (0);
}

int	initialize_rasterization_queues(t_frame *frame)
{
	unsigned int	i;

	i = 0;
	frame->transformed = create_raster_queue(800);
	if (!frame->transformed)
		return (1);
	frame->triangles_in_view = create_raster_queue(8000);
	if (!frame->triangles_in_view)
		return (1);
	frame->raster_queue = (t_raster_queue **)malloc(sizeof(t_raster_queue *)
			* (MAX_THREADS + 1));
	if (!frame->raster_queue)
		return (1);
	while (i < MAX_THREADS)
	{
		frame->raster_queue[i] = create_raster_queue(8000);
		if (!frame->raster_queue[i])
			return (1);
		i++;
	}
	if (initialize_viewport(&frame->viewport))
		return (1);
	ft_putendl("Raster queues created, and viewport initialized.");
	return (0);
}

void	free_entities(t_home *home)
{
	Uint32	i;

	i = 0;
	if (!home->entity_pool)
		return ;
	while (i < home->nbr_of_entities)
	{
		if (home->entity_pool[i])
		{
			free(home->entity_pool[i]);
			home->entity_pool[i] = NULL;
		}
		i++;
	}
	free(home->entity_pool);
	home->entity_pool = NULL;
}

void	free_projectiles(t_home *home)
{
	Uint32	i;

	i = MAX_PROJECTILES;
	if (!home->projectile_pool)
		return ;
	while (i--)
	{
		if (home->projectile_pool[i])
		{
			free(home->projectile_pool[i]);
			home->projectile_pool[i] = NULL;
		}
	}
	free(home->projectile_pool);
	home->projectile_pool = NULL;
}
