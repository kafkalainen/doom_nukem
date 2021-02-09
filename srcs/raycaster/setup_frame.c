/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:26:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/09 14:37:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void		setup_frame(t_frame *frame, t_frame *new_frame,
	float current_angle, int idx)
{
	new_frame->idx = idx;
	new_frame->old_idx = frame->idx;
	new_frame->min_step = frame->min_step;
	new_frame->offset = frame->offset - new_frame->min_step;
	new_frame->max_fov = (frame->offset - current_angle < 0) ? 0.0f : frame->offset - current_angle;
	new_frame->draw_surf = frame->draw_surf;
	new_frame->plr_offset = frame->plr_offset;
}
