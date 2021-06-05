/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_to_viewport_edges.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:19:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/05 11:19:58 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../headers/doom_nukem.h"

static void	viewport_logic(t_plane *plane, char choice, t_sides *viewport)
{
	if (choice == 0)
	{
		plane->point = viewport->top.point;
		plane->normal = viewport->top.normal;
	}
	else if (choice == 1)
	{
		plane->point = viewport->bottom.point;
		plane->normal = viewport->bottom.normal;
	}
	else if (choice == 2)
	{
		plane->point = viewport->left.point;
		plane->normal = viewport->left.normal;
	}
	else
	{
		plane->point = viewport->right.point;
		plane->normal = viewport->right.normal;
	}
}

static int	draw_polygon(Uint32 *buffer, float *depth_buffer, t_raster_queue *tri, t_texture *tex)
{
	int	i;

	i = tri->front;
	(void)depth_buffer;
	(void)tex;
	while (i <= tri->rear)
	{
		// draw_tex_triangle(buffer, depth_buffer, &tri->array[i], tex);
		ft_str_pxl(buffer, vec2(tri->array[i].p[0].x, tri->array[i].p[0].y), "0", (t_plx_modifier){white, 2});
		ft_str_pxl(buffer, vec2(tri->array[i].p[1].x, tri->array[i].p[1].y), "1", (t_plx_modifier){white, 2});
		ft_str_pxl(buffer, vec2(tri->array[i].p[2].x, tri->array[i].p[2].y), "2", (t_plx_modifier){white, 2});
		draw_line(vec2(tri->array[i].p[0].x, tri->array[i].p[0].y),
			vec2(tri->array[i].p[1].x, tri->array[i].p[1].y),
			tri->array[i].colour, buffer);
		draw_line(vec2(tri->array[i].p[1].x, tri->array[i].p[1].y),
			vec2(tri->array[i].p[2].x, tri->array[i].p[2].y),
			tri->array[i].colour, buffer);
		draw_line(vec2(tri->array[i].p[2].x, tri->array[i].p[2].y),
			vec2(tri->array[i].p[0].x, tri->array[i].p[0].y),
			tri->array[i].colour, buffer);
		i++;
	}
	return (TRUE);
}

static int	clip_to_an_edge(t_raster_queue *raster_list,
	t_plane *plane, int current_triangles)
{
	int			i;
	int			triangles_to_add;
	t_triangle	tested;
	t_triangle	clipped[2];

	triangles_to_add = 0;
	while (current_triangles > 0)
	{
		tested = raster_list->array[raster_list->front];
		dequeue(raster_list);
		current_triangles--;
		triangles_to_add = clip_against_plane(plane, &tested, &clipped[0], &clipped[1]);
		i = 0;
		while (i < triangles_to_add)
		{
			enqueue_to_raster(raster_list, &clipped[i]);
			i++;
		}
	}
	return (triangles_to_add);
}

static void	clipper_viewport_edges(t_sides *planes, t_raster_queue *raster_queue, t_arg *arg)
{
	int			i;
	int			current_plane;
	int			new_triangles;
	t_plane		plane;


	i = 0;
	while (i < arg->view_list->size)
	{
		raster_queue->rear = -1;
		raster_queue->front = -1;
		raster_queue->size = 0;
		enqueue_to_raster(raster_queue, &arg->view_list->array[i]);
		new_triangles = 1;
		current_plane = 0;
		while (current_plane < 4)
		{
			viewport_logic(&plane, current_plane, planes);
			new_triangles = clip_to_an_edge(raster_queue, &plane, new_triangles);
			current_plane++;
		}
		draw_polygon(arg->buffer, arg->depth_buffer, raster_queue, arg->tex);
		i++;
	}
}

void	*clip_to_viewport_edges(void *args)
{
	t_arg			*arg;
	pthread_t		current;
	unsigned int	index;
	t_raster_queue	*current_queue;
	t_sides			planes;

	index = 0;
	arg = (t_arg*)args;
	current = pthread_self();
	while (current != arg->tid[index] && index + 1 != MAX_THREADS)
		index++;
	planes = *(arg->viewport);
	planes.top = arg->viewport->mid_planes[index];
	planes.bottom = arg->viewport->mid_planes[index + 1];
	planes.bottom.point.y -= 1;
	planes.bottom.normal.y *= -1.0f;
	current_queue = arg->raster_queue[index];
	clipper_viewport_edges(&planes, current_queue, arg);
	return (NULL);
}
