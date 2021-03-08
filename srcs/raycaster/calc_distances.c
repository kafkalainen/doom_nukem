/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distances.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:27:42 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/08 14:07:02 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void	calc_distances(t_frame *frame)
{
	frame->l_perp_dist = fabs(frame->left.l_pt.x + 
		frame->left.l_pt.y) * SQR2;
	frame->r_perp_dist = fabs(frame->left.r_pt.x + 
		frame->left.r_pt.y) * SQR2;
	frame->l_full_perp_dist = fabs(frame->left.wall->x0.x + 
		frame->left.wall->x0.y) * SQR2;
	frame->r_full_perp_dist = fabs(frame->left.wall->next->x0.x + 
		frame->left.wall->next->x0.y) * SQR2;
	frame->wall_x1 = SCREEN_WIDTH - ((SCREEN_HEIGHT / 
		frame->l_perp_dist) * frame->left.l_pt.x);
	frame->wall_x2 = SCREEN_WIDTH - ((SCREEN_HEIGHT / 
		frame->r_perp_dist) * frame->left.r_pt.x);
	// if (frame->l_full_perp_dist != 0)
		frame->full_wall_x1 = SCREEN_WIDTH - ((SCREEN_HEIGHT / 
			frame->l_full_perp_dist) * frame->left.wall->x0.x);
	// else
		// frame->full_wall_x1 = SCREEN_WIDTH - frame->left.wall->x0.x;
	// if (frame->r_full_perp_dist != 0)
		frame->full_wall_x2 = SCREEN_WIDTH - ((SCREEN_HEIGHT / 
			frame->r_full_perp_dist) * frame->left.wall->next->x0.x);
	// else
		// frame->full_wall_x2 = SCREEN_WIDTH - frame->left.wall->next->x0.x;
	frame->wall_len = frame->wall_x2 - frame->wall_x1;
	//frame->full_wall_len = get_distance(frame->left.wall->x0, frame->left.wall->next->x0) * SCREEN_WIDTH / SCREEN_HEIGHT;
	frame->full_wall_len = frame->full_wall_x2 - frame->full_wall_x1;
	//frame->full_wall_len =
	frame->wall_h_l = SCREEN_HEIGHT / frame->l_perp_dist * 20;
	frame->wall_h_r = SCREEN_HEIGHT / frame->r_perp_dist * 20;
}
