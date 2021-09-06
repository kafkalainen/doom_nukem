/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 09:53:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/06 16:22:22 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	draw_wire_tri(t_buffer *buffer, t_triangle *tri, Uint32 colour)
{
	ft_str_pxl(buffer, vec2(tri->p[0].x, tri->p[0].y), "0",
		(t_plx_modifier){white, 2, 2});
	ft_str_pxl(buffer, vec2(tri->p[1].x, tri->p[1].y), "1",
		(t_plx_modifier){white, 2, 2});
	ft_str_pxl(buffer, vec2(tri->p[2].x, tri->p[2].y), "2",
		(t_plx_modifier){white, 2, 2});
	draw_line(vec2(tri->p[0].x, tri->p[0].y),
		vec2(tri->p[1].x, tri->p[1].y),
		colour, buffer);
	draw_line(vec2(tri->p[1].x, tri->p[1].y),
		vec2(tri->p[2].x, tri->p[2].y),
		colour, buffer);
	draw_line(vec2(tri->p[2].x, tri->p[2].y),
		vec2(tri->p[0].x, tri->p[0].y),
		colour, buffer);
}

void	draw_wireframe(t_frame *frame, Uint32 colour)
{
	int		i;

	i = frame->triangles_in_view->front;
	if (frame->triangles_in_view->size > 0)
	{
		while (i <= frame->triangles_in_view->rear)
		{
			draw_wire_tri(&frame->buffer, &frame->triangles_in_view->array[i],
				colour);
			i++;
		}
	}
}
