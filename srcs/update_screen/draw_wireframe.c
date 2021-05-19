/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 09:53:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/19 11:58:45 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	draw_top(t_frame *frame, Uint32 colour)
{
	draw_line(vec3_to_vec2(frame->inner_box.top_left),
		vec3_to_vec2(frame->inner_box.top_right),
		colour, frame->buffer);
	draw_line(vec3_to_vec2(frame->outer_box.top_left),
		vec3_to_vec2(frame->outer_box.top_right),
		colour, frame->buffer);
}

static void	draw_middle(t_frame *frame, Uint32 colour)
{
	draw_line(vec3_to_vec2(frame->outer_box.top_left),
		vec3_to_vec2(frame->outer_box.top_right), colour,
		frame->buffer);
	draw_line(vec3_to_vec2(frame->outer_box.bottom_left),
		vec3_to_vec2(frame->outer_box.bottom_right),
		colour, frame->buffer);
	draw_line(vec3_to_vec2(frame->outer_box.top_left),
		vec3_to_vec2(frame->outer_box.bottom_left),
		colour, frame->buffer);
	draw_line(vec3_to_vec2(frame->outer_box.top_right),
		vec3_to_vec2(frame->outer_box.bottom_right),
		colour, frame->buffer);
}

static void	draw_bottom(t_frame *frame, Uint32 colour)
{
	draw_line(vec3_to_vec2(frame->inner_box.bottom_left),
		vec3_to_vec2(frame->inner_box.bottom_right),
		colour, frame->buffer);
	draw_line(vec3_to_vec2(frame->outer_box.bottom_left),
		vec3_to_vec2(frame->outer_box.bottom_right),
		colour, frame->buffer);
}

void	draw_wireframe(t_frame *frame, Uint32 colour)
{
	if (frame->draw_top)
		draw_top(frame, colour);
	if (frame->draw_middle)
		draw_middle(frame, colour);
	if (frame->draw_bottom)
		draw_bottom(frame, colour);
}
