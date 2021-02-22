/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:26:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/22 10:59:37 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void		setup_frame(t_frame *frame, t_frame *new_frame,
	int current_pxl, int idx)
{
	new_frame->idx = idx;
	new_frame->old_idx = frame->idx;
	new_frame->min_step = frame->min_step;
	/*max_fov needs to be properly bounded. If min_step is not added, calculation is stuck in an infinite loop.*/
	//new_frame->max_fov = frame->offset - current_pxl;
	new_frame->max_fov = (frame->offset - current_pxl < 0) ? 0.0f : frame->offset - current_pxl + 1;
	/*If this value is changed to just offset, the calculation will be stuck in the infinite loop.*/
	//new_frame->offset = frame->offset - frame->min_step;
	new_frame->offset = frame->offset - 1;
	new_frame->draw_surf = frame->draw_surf;
	new_frame->plr_offset = frame->plr_offset;
	new_frame->pxl_offset = frame->pxl_offset;
}
