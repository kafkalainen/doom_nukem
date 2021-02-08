/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:26:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/08 12:17:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void		setup_frame(t_frame *frame, t_frame *new_frame,
	float fov_angle, int idx)
{
	int		new_fov;

	new_fov = SCREEN_WIDTH * fov_angle;
	new_frame->idx = idx;
	new_frame->old_idx = frame->idx;
	new_frame->offset = frame->offset;
	new_frame->fov_angle = fov_angle;
	new_frame->max_fov = (new_fov + new_frame->offset > 640) ? 640 : new_fov + new_frame->offset;
	new_frame->draw_surf = frame->draw_surf;
	new_frame->plr_offset = frame->plr_offset;
}
