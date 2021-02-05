/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 07:59:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/05 12:20:00 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void			scan_fov(t_home *home, t_frame *frame)
{
	t_ray_fov	fov;
	t_frame		new_frame;
	float		angle;
	int			new_fov;

	while (frame->offset < frame->max_fov)
	{
		get_left_point(home->sectors[frame->idx]->points, &fov, frame->offset);
		angle = vec2_angle(fov.left_point, fov.right_point);
		new_fov = SCREEN_WIDTH * angle / (FOV * DEG_TO_RAD);
		if (fov.left_wall->idx > 0)
		{
			setup_frame(frame, &new_frame, fov.left_wall->idx, new_fov);
			scan_fov(home, &new_frame);
		}
		ft_draw_line(
			vec2_add(fov.left_point, home->offset),
			vec2_add(fov.right_point, home->offset),
			green,
			frame->draw_surf
		);
		new_fov = new_fov < MARGIN ? 1 : new_fov;
		frame->offset = new_fov + frame->offset;
	}
}
