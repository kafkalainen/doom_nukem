/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_to_viewport_edges.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:19:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/07 13:05:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../headers/doom_nukem.h"

static void	viewport_logic(t_plane *plane, char choice, t_planes planes)
{
	if (choice == 0)
	{
		plane->point = planes.top.point;
		plane->normal = planes.top.normal;
	}
	else if (choice == 1)
	{
		plane->point = planes.bottom.point;
		plane->normal = planes.bottom.normal;
	}
	else if (choice == 2)
	{
		plane->point = planes.left.point;
		plane->normal = planes.left.normal;
	}
	else
	{
		plane->point = planes.right.point;
		plane->normal = planes.right.normal;
	}
}

static void	draw_polygon(t_buffer *buffer, float *depth_buffer,
	t_raster_queue *tri, t_texel *tex)
{
	int		i;

	i = tri->front;
	while (i <= tri->rear)
	{
		draw_tex_triangle(buffer, depth_buffer, &tri->array[i], tex);
		i++;
	}
}

static int	clip_to_an_edge(t_raster_queue *raster_list,
	t_plane plane, int current_triangles)
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
		triangles_to_add = clip_to_plane(&plane, &tested,
				&clipped[0], &clipped[1]);
		i = 0;
		while (i < triangles_to_add)
		{
			enqueue_to_raster(raster_list, &clipped[i]);
			i++;
		}
	}
	return (triangles_to_add);
}

static void	clipper_viewport_edges(t_planes planes,
			t_raster_queue *raster_queue, t_arg *arg, int i)
{
	int			current_plane;
	int			new_triangles;
	t_plane		plane;
	t_texel		*tex;

	while (i < arg->view_list->size)
	{
		quick_reset_queue(raster_queue);
		enqueue_to_raster(raster_queue, &arg->view_list->array[i]);
		new_triangles = 1;
		current_plane = 0;
		while (current_plane < 4)
		{
			viewport_logic(&plane, current_plane, planes);
			clip_to_an_edge(raster_queue, plane, new_triangles);
			new_triangles = raster_queue->size;
			current_plane++;
		}
		tex = get_tex(arg->view_list->array[i].type, arg->textures);
		draw_polygon(arg->buffer, arg->depth_buffer, raster_queue, tex);
		i++;
	}
}

void	*clip_to_viewport_edges(void *args)
{
	t_arg			*arg;
	unsigned int	index;
	t_raster_queue	*current_queue;
	t_planes		planes;
	int				i;

	index = 0;
	i = 0;
	arg = (t_arg *)args;
	index = arg->thread_index;
	planes.top = arg->viewport->mid_planes[index];
	planes.bottom = arg->viewport->mid_planes[index + 1];
	planes.bottom.normal.y *= -1.0f;
	planes.left = arg->viewport->left;
	planes.right = arg->viewport->right;
	current_queue = arg->raster_queue[index];
	clipper_viewport_edges(planes, current_queue, arg, i);
	return (NULL);
}
