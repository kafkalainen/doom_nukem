/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 11:35:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/07 13:40:00 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	painters_algorithm(const void *tri1, const void *tri2)
{
	if (triangle_calculate_average_z((t_triangle *)tri1)
		< triangle_calculate_average_z((t_triangle *)tri2))
		return (1);
	else
		return (0);
}

static Uint32	transform_walls(t_home *home, t_sector *sector, t_raster_queue *transformed)
{
	Uint32		i;
	Uint32		j;
	Uint32		k;
	t_wall		*wall;
	t_surface	*surface;

	i = 0;
	j = 0;
	k = 0;
	wall = sector->walls;
	surface = sector->ground;
	while (i < 12)
	{
		transformed->array[i] = apply_world_matrix(0.0f, 0.0f, (t_xyz){-50.0f, -50.0f, -50.0f, 0.0f}, &home->skybox.face[i]);
		i++;
	}
	while (j < sector->nb_of_walls * 2)
	{
		transformed->array[i] = apply_world_matrix(0.0f, 0.0f, (t_xyz){0.0f, 0.0f, 5.0f, 0.0f}, &wall->top);
		i++;
		j++;
		transformed->array[i] = apply_world_matrix(0.0f, 0.0f, (t_xyz){0.0f, 0.0f, 5.0f, 0.0f}, &wall->bottom);
		i++;
		j++;
		wall = wall->next;
	}
	while (k < 2)
	{
		transformed->array[i] = apply_world_matrix(0.0f, 0.0f, (t_xyz){0.0f, 0.0f, 5.0f, 0.0f}, &surface->tri);
		i++;
		k++;
		surface = surface->next;
	}
	transformed->size = i;
	return (TRUE);
}

static Uint32	clip_to_near_plane(t_triangle *current_view,
	t_sides *viewport, t_raster_queue *triangles_in_view)
{
	Uint32		nb_of_clipped_triangles;
	t_triangle	projected;
	t_xyz		scale;
	t_triangle	clipped_triangle[2];

	scale = (t_xyz){0.5 * SCREEN_WIDTH, 0.5 * SCREEN_HEIGHT, 1.0f, 1.0f};
	nb_of_clipped_triangles = clip_against_plane(&viewport->near,
		current_view, &clipped_triangle[0], &clipped_triangle[1]);
	while (nb_of_clipped_triangles)
	{
		projected = create_projection(&clipped_triangle[nb_of_clipped_triangles - 1]);
		triangle_inv_z(&projected);
		projected.p[0] = vec3_div(projected.p[0], projected.p[0].w);
		projected.p[1] = vec3_div(projected.p[1], projected.p[1].w);
		projected.p[2] = vec3_div(projected.p[2], projected.p[2].w);
		invert_view(&projected);
		triangle_add(&projected, viewport->view_offset);
		projected = scale_triangle(&projected, scale);
		triangles_in_view->array[triangles_in_view->size] = projected;
		triangles_in_view->size++;
		nb_of_clipped_triangles--;
	}
	return (TRUE);
}

static Uint32	project_to_player_position(t_raster_queue *transformed,
	t_raster_queue *triangles_in_view, t_player *plr, t_sides *view)
{
	Uint32		i;
	size_t		current_size;
	t_xyz		normal;
	t_triangle	current_viewed_triangle;

	create_target_vector(plr);
	current_size = transformed->size;
	triangles_in_view->size = 0;
	i = 0;
	while (i < current_size)
	{
		normal = triangle_normal(&transformed->array[i]);
		if (vec3_dot_product(normal, vec3_dec(transformed->array[i].p[0], plr->camera)) > 0)
		{
			current_viewed_triangle = apply_camera(
				plr->camera, plr->target, plr->up, &transformed->array[i]);
			clip_to_near_plane(&current_viewed_triangle, view, triangles_in_view);
		}
		i++;
	}
	return (TRUE);
}

int	draw_sector(t_frame *frame, t_home *home, t_sector *sector, t_player *plr)
{
	t_arg			args;
	Uint32			i;

	i = 0;
	transform_walls(home, sector, frame->transformed);
	project_to_player_position(frame->transformed, frame->triangles_in_view, plr, &frame->viewport);
	// qsort((void *)frame->triangles_in_view->array,
	// 	(size_t)frame->triangles_in_view->size, sizeof(t_triangle), painters_algorithm);
	while (i < SCREEN_HEIGHT * SCREEN_WIDTH)
	{
		frame->depth_buffer[i] = 0.0f;
		i++;
	}
	args.editor_tex = home->editor_tex;
	args.buffer = frame->buffer;
	args.depth_buffer = frame->depth_buffer;
	args.view_list = frame->triangles_in_view;
	args.raster_queue = frame->raster_queue;
	args.viewport = &frame->viewport;
	args.last_frame = home->t.frame_time_last;
	// clip_to_viewport_edges((void*)&args);
	i = 0;
	while (i < MAX_THREADS)
	{
		pthread_create(&args.tid[i], NULL, &clip_to_viewport_edges, (void*)&args);
		i++;
	}
	while (i--)
		pthread_join(args.tid[i], NULL);
	return (TRUE);
}
