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
	frame->left_perp_dist = fabs(frame->left.left_point.x + frame->left.left_point.y) * SQR2;
	frame->right_perp_dist = fabs(frame->left.right_point.x + frame->left.right_point.y) * SQR2;
	frame->wall_x1 = SCREEN_WIDTH - ((SCREEN_HEIGHT / frame->left_perp_dist) * frame->left.left_point.x);
	frame->wall_x2 = SCREEN_WIDTH - ((SCREEN_HEIGHT / frame->right_perp_dist) * frame->left.right_point.x);
	frame->wall_len = frame->wall_x2 - frame->wall_x1;
	frame->wall_height_left = SCREEN_HEIGHT / frame->left_perp_dist * 20;
	frame->wall_height_right = SCREEN_HEIGHT / frame->right_perp_dist * 20;
}
