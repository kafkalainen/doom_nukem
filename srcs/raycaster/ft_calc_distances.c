/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_distances.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:27:42 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/02 09:30:37 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void	ft_calc_distances(t_frame *frame)
{
	frame->l_perp_dist = fabs(frame->left.l_pt.x + 
		frame->left.l_pt.y) * SQR2;
	frame->r_perp_dist = fabs(frame->left.r_pt.x + 
		frame->left.r_pt.y) * SQR2;
	frame->wall_x1 = SCREEN_WIDTH - ((SCREEN_HEIGHT / 
		frame->l_perp_dist) * frame->left.l_pt.x);
	frame->wall_x2 = SCREEN_WIDTH - ((SCREEN_HEIGHT / 
		frame->r_perp_dist) * frame->left.r_pt.x);
	frame->wall_len = frame->wall_x2 - frame->wall_x1;
	frame->wall_h_l = SCREEN_HEIGHT / frame->l_perp_dist * 20;
	frame->wall_h_r = SCREEN_HEIGHT / frame->r_perp_dist * 20;
}
