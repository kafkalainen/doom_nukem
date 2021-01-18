/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steplen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:29:47 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/18 11:51:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

t_step	*steplen(t_step *ground, int current_y, t_ray_floor hor,
	t_player *plr)
{
	double		row_dist;

	row_dist = (0.5 * SCREEN_HEIGHT) / (current_y - SCREEN_HEIGHT * 0.5);
	ground->step_len.x = row_dist * (hor.right.x - hor.left.x) / SCREEN_WIDTH;
	ground->step_len.y = row_dist * (hor.right.y - hor.left.y) / SCREEN_WIDTH;
	ground->cur_step.x = plr->pos.x + row_dist * hor.left.x;
	ground->cur_step.y = plr->pos.y + row_dist * hor.left.y;
	return (ground);
}
