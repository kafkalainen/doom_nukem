/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distances.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:27:42 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/08 16:52:44 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void	calc_distances(t_frame *frame)
{
	frame->l_perp_dist = fabs(frame->left.l_pt.x + 
		frame->left.l_pt.y) * SQR2;
	frame->r_perp_dist = fabs(frame->left.r_pt.x + 
		frame->left.r_pt.y) * SQR2;
	frame->wall_x1 = SCREEN_WIDTH - ((SCREEN_HEIGHT / 
		frame->l_perp_dist) * frame->left.l_pt.x);
	frame->wall_x2 = SCREEN_WIDTH - ((SCREEN_HEIGHT / 
		frame->r_perp_dist) * frame->left.r_pt.x);
	frame->visible_wall_dist = get_distance(frame->left.l_pt, frame->left.r_pt);
	frame->full_wall_dist = get_distance(frame->left.wall->x0, frame->left.wall->next->x0);
	frame->wall_len = frame->wall_x2 - frame->wall_x1;
	frame->full_wall_len = frame->wall_len * (frame->full_wall_dist / frame->visible_wall_dist);
	frame->wall_h_l = SCREEN_HEIGHT / frame->l_perp_dist * 20;
	frame->wall_h_r = SCREEN_HEIGHT / frame->r_perp_dist * 20;
}
