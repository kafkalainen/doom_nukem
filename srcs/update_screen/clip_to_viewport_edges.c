/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_to_viewport_edges.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:19:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/31 19:51:03 by jnivala          ###   ########.fr       */
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

static int	draw_polygon(t_frame *frame, t_raster_queue *tri, t_texture *tex)
{
	int	i;

	i = tri->front;
	(void)tex;
	while (i <= tri->rear)
	{
		draw_tex_triangle(frame, &tri->array[i], tex);
		draw_line(vec2(tri->array[i].p[0].x, tri->array[i].p[0].y),
			vec2(tri->array[i].p[1].x, tri->array[i].p[1].y),
			tri->array[i].colour, frame->buffer);
		draw_line(vec2(tri->array[i].p[1].x, tri->array[i].p[1].y),
			vec2(tri->array[i].p[2].x, tri->array[i].p[2].y),
			tri->array[i].colour, frame->buffer);
		draw_line(vec2(tri->array[i].p[2].x, tri->array[i].p[2].y),
			vec2(tri->array[i].p[0].x, tri->array[i].p[0].y),
			tri->array[i].colour, frame->buffer);
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
			enqueue_to_raster(raster_list, clipped[i]);
			i++;
		}
	}
	return (triangles_to_add);
}

int	clip_to_viewport_edges(t_raster_queue *view_list, t_raster_queue *raster_list,
	t_sides *viewport, t_frame *frame, t_texture *tex)
{
	int			i;
	int			current_plane;
	int			new_triangles;
	t_plane		plane;

	i = 0;
	while (i < view_list->size)
	{
		raster_list->rear = -1;
		raster_list->front = -1;
		raster_list->size = 0;
		enqueue_to_raster(raster_list, view_list->array[i]);
		new_triangles = 1;
		current_plane = 0;
		while (current_plane < 4)
		{
			viewport_logic(&plane, current_plane, viewport);
			new_triangles = clip_to_an_edge(raster_list, &plane, new_triangles);
			current_plane++;
		}
		draw_polygon(frame, raster_list, tex);
		i++;
	}
	return (raster_list->size);
}
