/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_to_viewport_edges.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:19:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/27 14:22:55 by jnivala          ###   ########.fr       */
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

static int	clipping_loop(t_triangle *raster_list,
	t_plane plane, int amount_to_be_clipped)
{
	t_triangle	tested;
	t_triangle	clipped[2];
	int			j;
	int			amount_to_be_added;

	amount_to_be_added = 0;
	while (amount_to_be_clipped)
	{
		tested = *raster_list;
		amount_to_be_clipped--;
		amount_to_be_added = clip_against_plane(&plane, &tested, &clipped[0], &clipped[1]);
		j = 0;
		while (j < amount_to_be_added)
		{
			*raster_list = clipped[j];
			raster_list++;
			j++;
		}
	}
	return (amount_to_be_added);
}

int	clip_to_viewport_edges(t_triangle *view_list, t_triangle *raster_list,
	t_sides *viewport, int nb_of_triangles_in_view)
{
	int			i;
	int			clipped_amount;
	int			raster_triangles_count;
	char		current_plane;
	t_triangle	*current_list_pos;

	i = 0;
	raster_triangles_count = 0;
	current_list_pos = raster_list;
	while (i < nb_of_triangles_in_view)
	{
		*current_list_pos = view_list[i];
		clipped_amount = 1;
		current_plane = 0;
		while (current_plane < 4)
		{
			clipped_amount = clipping_loop(current_list_pos,
				viewport_logic(current_plane, viewport), clipped_amount);
			current_plane++;
			if (clipped_amount - 1 > 0)
				raster_triangles_count += 1;
		}
		current_list_pos += clipped_amount;
		raster_triangles_count++;
		i++;
	}
	return (raster_triangles_count);
}
