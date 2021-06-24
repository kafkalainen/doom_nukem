/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 11:35:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/24 15:08:11 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

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
		triangles_in_view->size += 1;
		nb_of_clipped_triangles--;
	}
	return (TRUE);
}

// static Uint32	project_to_player_position(t_raster_queue *transformed,
// 	t_raster_queue *triangles_in_view, t_player *plr, t_sides *view)

static Uint32	project_to_player_position(t_frame *frame, t_player *plr, t_xyz	light_src)
{
	Uint32		i;
	size_t		current_size;
	t_xyz		normal;
	t_triangle	current_viewed_triangle;

	create_target_vector(plr);
	current_size = frame->transformed->size;
	frame->triangles_in_view->size = 0;
	i = 0;
	while (i < current_size)
	{
		normal = triangle_normal(&frame->transformed->array[i]);
		if (vec3_dot_product(normal, vec3_dec(frame->transformed->array[i].p[0],
			plr->pos)) < 0)
		{
			frame->transformed->array[i].illumination = ft_fmax(
				vec3_dot_product(light_src, normal), 0.1f);
			current_viewed_triangle = apply_camera(
				plr->pos, plr->target, plr->up, &frame->transformed->array[i]);
			clip_to_near_plane(&current_viewed_triangle, &frame->viewport,
				frame->triangles_in_view);
		}
		i++;
	}
	return (TRUE);
}

void	reset_depth_buffer(float *depth_buffer)
{
	int i;

	i = 0;
	while (i < (SCREEN_HEIGHT * SCREEN_WIDTH))
	{
		depth_buffer[i] = 0.0f;
		i++;
	}
}


// if (sector_idx == -1)
// 	project_to_player_position(frame, plr, (t_xyz){});
// else
// 	project_to_player_position(frame, plr, home->sectors[sector_idx]->)

static void	initialize_thread(t_arg *arg, t_frame *frame, t_home *home, Uint32 idx)
{
	arg->textures = home->textures;
	arg->buffer = frame->buffer;
	arg->depth_buffer = frame->depth_buffer;
	arg->view_list = frame->triangles_in_view;
	arg->raster_queue = frame->raster_queue;
	arg->viewport = &frame->viewport;
	arg->last_frame = home->t.frame_time_last;
	arg->thread_index = idx;
}

int	draw_sector(t_frame *frame, t_home *home, t_player *plr, int sector_idx)
{
	t_arg			args[MAX_THREADS];
	pthread_t		tid[MAX_THREADS];
	pthread_mutex_t	mutex;
	Uint32			i;

	i = 0;
	(void)sector_idx;
	mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	project_to_player_position(frame, plr, (t_xyz){0.0f, 1.0f, 0.0f, 0.0f});
	while (i < MAX_THREADS)
	{
		initialize_thread(&args[i], frame, home, i);
		pthread_create(&tid[i], NULL, &clip_to_viewport_edges, (void*)&args[i]);
		pthread_mutex_lock(&mutex);
		i++;
		pthread_mutex_unlock(&mutex);
	}
	while (i--)
		pthread_join(tid[i], NULL);
	return (TRUE);
}
