/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 11:35:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/28 16:00:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	clip_to_near_and_far_plane(t_triangle *cur,
	t_sides *viewport, t_raster_queue *triangles_in_view)
{
	t_uint		clip_count[2];
	t_triangle	near[2];
	t_triangle	far[2];

	if (cur->type == -space)
	{
		far[0] = *cur;
		clip_count[0] = 1;
	}
	else
		clip_count[0] = clip_to_plane(&viewport->far, cur, &far[0], &far[1]);
	while (clip_count[0])
	{
		clip_count[1] = clip_to_plane(&viewport->near,
				&far[clip_count[0] - 1], &near[0], &near[1]);
		while (clip_count[1])
		{
			triangles_in_view->array[triangles_in_view->size]
				= project_to_screen_space(&near[clip_count[1] - 1],
					viewport->view_offset, viewport->scale);
			triangles_in_view->size += 1;
			clip_count[1]--;
		}
		clip_count[0]--;
	}
}

static void	project_to_player_position(t_frame *frame, t_player *plr,
	t_lighting *lights)
{
	t_triangle	viewed_tri;
	t_bool		visible;

	create_target_vector(plr);
	quick_reset_queue(frame->triangles_in_view);
	while (frame->transformed->size)
	{
		front(frame->transformed, &viewed_tri);
		visible = is_triangle_visible(&viewed_tri, plr->pos);
		if (visible)
			set_lighting(lights, &viewed_tri);
		else if (!visible && viewed_tri.hull)
			show_hull(&viewed_tri);
		if (visible || (!visible && viewed_tri.hull))
		{
			viewed_tri = apply_camera(plr, &viewed_tri);
			clip_to_near_and_far_plane(&viewed_tri, &frame->viewport,
				frame->triangles_in_view);
		}
		dequeue(frame->transformed);
	}
}

void	reset_depth_buffer(float *depth_buffer)
{
	int	i;

	i = 0;
	while (i < (SCREEN_HEIGHT * SCREEN_WIDTH))
	{
		depth_buffer[i] = 0.0f;
		i++;
	}
}

static void	initialize_thread(t_arg *arg, t_frame *frame, t_home *home,
			Uint32 idx)
{
	arg->textures = home->textures;
	arg->buffer = &frame->buffer;
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
	mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	project_to_player_position(frame, plr,
		&home->sectors[sector_idx]->lights);
	while (i < MAX_THREADS)
	{
		initialize_thread(&args[i], frame, home, i);
		pthread_create(&tid[i], NULL, &clip_to_viewport_edges,
			(void*)&args[i]);
		pthread_mutex_lock(&mutex);
		i++;
		pthread_mutex_unlock(&mutex);
	}
	while (i--)
		pthread_join(tid[i], NULL);
	return (TRUE);
}
