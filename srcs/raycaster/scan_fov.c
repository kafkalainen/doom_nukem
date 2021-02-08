/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 07:59:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/08 12:22:56 by jnivala          ###   ########.fr       */
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
	float		angle;
	int			new_fov;

	fov.left_point = vec2(-1,-1);
	fov.left_wall = home->sectors[frame->idx]->points;
	continue_from_last_sector(fov.left_wall, &fov, frame);
	while (frame->offset < frame->max_fov)
	{
		if (frame->offset != 0)
			continue_from_next_point(fov.left_wall, &fov, frame);
		else
			get_left_point(fov.left_wall, &fov, frame, home->sectors[frame->idx]->nb_of_walls);
		angle = vec2_angle(fov.left_point, fov.right_point);
		new_fov = SCREEN_WIDTH * angle;
		if (check_if_portal(fov.left_wall, frame))
		{
			setup_frame(frame, &new_frame, angle, fov.left_wall->idx);
			scan_fov(home, &new_frame);
			frame->offset = new_frame.offset;
		}
		else
		{
			ft_draw_line(
			vec2_add(fov.left_point, home->offset),
			vec2_add(fov.right_point, home->offset),
			green,
			frame->draw_surf);
			new_fov = new_fov < MARGIN ? 1 : new_fov;
			frame->offset = new_fov + frame->offset;
		}
	}
}
