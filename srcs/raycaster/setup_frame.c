/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:26:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/10 13:33:55 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	setup_frame(t_frame *frame, t_frame *new_frame, int idx)
{
	new_frame->idx = idx;
	new_frame->old_idx = frame->idx;
	new_frame->offset = frame->offset;
	new_frame->buffer = frame->buffer;
	new_frame->transformed = frame->transformed;
	new_frame->triangles_in_view = frame->triangles_in_view;
	new_frame->raster_queue = frame->raster_queue;
	new_frame->viewport = frame->viewport;
	new_frame->depth_buffer = frame->depth_buffer;
}
