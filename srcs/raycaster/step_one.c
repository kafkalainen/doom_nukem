/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:45:45 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/21 16:45:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	step_one(t_xyz *start, t_xyz *bottom, size_t *obj_x, t_frame *frame)
{
	start->y -= frame->step.y;
	bottom->y += frame->step.y;
	start->z -= frame->step.z;
	frame->uv_top_left.x += frame->uv_step.x;
	frame->uv_top_left.z += frame->uv_step.z;
	*obj_x = *obj_x + 1;
}
