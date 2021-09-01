/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:26:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/01 11:25:35 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// static t_wall	*retrieve_previous_portal(t_wall *wall, int old_idx)
// {
// 	t_wall	*new_wall;

// 	new_wall = wall;
// 	while (new_wall->top.idx != old_idx)
// 	{
// 		new_wall = new_wall->next;
// 	}
// 	return (new_wall);
// }

/*
**	We use portal occlusion culling.
**	Once we reach a portal, we calculate two vectors based on the portal isection
**	points.
*/
void	setup_frame(t_frame *frame, t_frame *new_frame, t_xy pos, int idx)
{
	new_frame->idx = idx;
	new_frame->old_idx = frame->idx;
	new_frame->buffer = frame->buffer;
	new_frame->transformed = frame->transformed;
	new_frame->triangles_in_view = frame->triangles_in_view;
	new_frame->raster_queue = frame->raster_queue;
	new_frame->viewport = frame->viewport;
	new_frame->depth_buffer = frame->depth_buffer;
	new_frame->left.dir = vec2_unit_vector(vec2_dec(frame->left.isection, pos));
	if (frame->right.wall == frame->left.wall)
	{
		new_frame->left.dir = vec2_unit_vector(vec2_dec(frame->left.isection, pos));
		new_frame->right.dir = vec2_unit_vector(vec2_dec(frame->right.isection, pos));
	}
	else if (frame->right.wall->top.idx != idx)
		new_frame->right.dir = vec2_unit_vector(vec2_dec(
			vec2(frame->left.wall->top.p[2].x, frame->left.wall->top.p[2].z), pos));
	else
		new_frame->right.dir = vec2_unit_vector(vec2_dec(frame->right.isection, pos));
}
