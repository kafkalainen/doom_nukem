/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 07:59:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/09 09:04:48 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"
/*
** TODO:
** Continue from last sector.
*/
void			scan_fov(t_home *home, t_frame *frame)
{
	t_ray_fov	fov;
	t_frame		new_frame;
	float		current_angle;

	current_angle = 0.0f;
	fov.left_point = vec2(-1,-1);
	fov.left_wall = home->sectors[frame->idx]->points;
	continue_from_last_sector(fov.left_wall, &fov, frame);
	get_left_point(fov.left_wall, &fov, frame, home->sectors[frame->idx]->nb_of_walls);
	while (current_angle + frame->offset < frame->max_fov)
	{
		if (current_angle != 0)
			continue_from_next_point(fov.left_wall, &fov, frame);
		current_angle = vec2_angle(fov.left_point, fov.right_point);
		// if (check_if_portal(fov.left_wall, frame))
		// {
		// 	setup_frame(frame, &new_frame, angle, fov.left_wall->idx);
		// 	scan_fov(home, &new_frame);
		// 	frame->offset = new_frame.offset;
		// }
		// else
		// {
			ft_draw_line(
				vec2_add(fov.left_point, home->offset),
				vec2_add(fov.right_point, home->offset),
				green,
				frame->draw_surf);
			frame->offset = frame->offset + current_angle;
		// }
	}
}
