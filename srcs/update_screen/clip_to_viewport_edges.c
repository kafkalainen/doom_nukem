/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_to_viewport_edges.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:19:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/27 20:39:50 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../headers/doom_nukem.h"

static t_plane	viewport_logic(char choice, t_sides *viewport)
{
	t_plane	plane;

	if (choice == 0)
	{
		plane.point = viewport->left.point;
		plane.normal = viewport->left.normal;
	}
	if (choice == 1)
	{
		plane.point = viewport->right.point;
		plane.normal = viewport->right.normal;
	}
	if (choice == 2)
	{
		plane.point = viewport->bottom.point;
		plane.normal = viewport->bottom.normal;
	}
	if (choice == 3)
	{
		plane.point = viewport->top.point;
		plane.normal = viewport->top.normal;
	}
	return (plane);
}

// static int	clipping_loop(t_triangle *raster_list,
// 	t_plane plane, int amount_to_be_clipped)
// {
// 	t_triangle	tested;
// 	t_triangle	clipped[2];
// 	int			j;
// 	int			amount_to_be_added;

// 	amount_to_be_added = 0;
// 	while (amount_to_be_clipped)
// 	{
// 		tested = *raster_list;
// 		amount_to_be_clipped--;
// 		amount_to_be_added = clip_against_plane(&plane, &tested, &clipped[0], &clipped[1]);
// 		j = 0;
// 		while (j < amount_to_be_added)
// 		{
// 			*raster_list = clipped[j];
// 			raster_list++;
// 			j++;
// 		}
// 	}
// 	return (amount_to_be_added);
// }

// static int	plane_loop(t_triangle *current_list_pos, t_sides *viewport)
// {

// 	int	new_triangles;

// 	new_triangles = 1;
// 	while (current_plane < 4)
// 	{
// 		temp = clipping_loop(current_list_pos,
// 			viewport_logic(current_plane, viewport), new_triangles);
// 		if (new_triangles > temp)
// 			new_triangles = temp;
// 		current_plane++;
// 	}
// 	return (new_triangles);
// }

static int	draw_polygon(t_frame *frame, t_raster_queue *tri)
{
	size_t	list;
	size_t	i;

	i = 0;
	list = tri->size;
	while (i < list)
	{
		draw_line(vec2(tri->array[i].p[0].x, tri->array[i].p[0].y), vec2(tri->array[i].p[1].x, tri->array[i].p[1].y),
			tri->array[i].colour, frame->buffer);
		draw_line(vec2(tri->array[i].p[1].x, tri->array[i].p[1].y), vec2(tri->array[i].p[2].x, tri->array[i].p[2].y),
			tri->array[i].colour, frame->buffer);
		draw_line(vec2(tri->array[i].p[2].x, tri->array[i].p[2].y), vec2(tri->array[i].p[0].x, tri->array[i].p[0].y),
			tri->array[i].colour, frame->buffer);
		list--;
	}
	return (TRUE);
}

/* Clipping loop returns 0, 1 or 2 based on how many triangles it has created.*/
int	clip_to_viewport_edges(t_triangle *view_list, t_raster_queue *raster_list,
	t_sides *viewport, int nb_of_triangles_in_view, t_frame *frame)
{
	int			i;
	int			w;
	int			new_triangles;
	int			triangles_to_add;
	int			current_plane;
	t_triangle	clipped[2];
	t_triangle	tested;
	t_plane		plane;

	i = 0;
	while (i < nb_of_triangles_in_view)
	{
		enqueue_to_raster(raster_list, view_list[i]);
		new_triangles = 1;
		current_plane = 0;
		while (current_plane < 4)
		{
			triangles_to_add = 0;
			while (new_triangles > 0)
			{
				front(raster_list, &tested);
				dequeue(raster_list);
				new_triangles--;
				plane = viewport_logic(current_plane, viewport);
				triangles_to_add = clip_against_plane(&plane, &tested, &clipped[0], &clipped[1]);
				w = 0;
				while (w < triangles_to_add)
				{
					enqueue_to_raster(raster_list, clipped[w]);
					w++;
				}
			}
			new_triangles = raster_list->size;
			current_plane++;
		}
		draw_polygon(frame, raster_list);
		i++;
	}
	raster_list->size = 0;
	return (raster_list->size);
}

//while (i < nb_of_triangles in view)
// {
//	w
//	clipped[2]
//	tested
//	array[]
//	array++;
//  *array = view_list[i]
//	Add item to the back of the array.
//	new_triangles = 1;
// 	Declaration of new_triangles
//	while (planes < 4)
//	{
//		triangles_to_add = 0;
//		while (new_triangles > 0)
//		{
//			tested = *array.front.item;
//			*array.pop.front();
//			new_triangles--;
//			current_plane_search
//			triangles_to_add = clipper;
//			while (w < triangles_to_add)
//			{
//				*array.push.back;
//			}
//
//
//		}
//	}
// }
