/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 07:59:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/09 14:44:49 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

static void		ft_draw_wall(t_frame *frame, float current_angle, int color)
{
	float		screen_width;
	float		screen_offset;
	int			i;

	i = 0;
	screen_width =	SCREEN_WIDTH / FOV * (current_angle * RAD_TO_DEG);
	screen_offset = SCREEN_WIDTH / FOV * (FOV - frame->offset * RAD_TO_DEG);
	while (i < (int)screen_width)
	{
		ft_draw_line(vec2(screen_offset + i, 0), vec2(screen_offset + i, 100), color, frame->draw_surf);
		i++;
	}
}

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
	while (frame->offset >= frame->max_fov)
	{
		if (current_angle != 0)
			continue_from_next_point(fov.left_wall, &fov, frame);
		current_angle = vec2_angle(fov.left_point, fov.right_point);
		if (check_if_portal(fov.left_wall, frame) && !check_if_same_point(current_angle, &fov))
		{
			setup_frame(frame, &new_frame, current_angle, fov.left_wall->idx);
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
			ft_draw_wall(frame, current_angle, 0xFF8000 + frame->offset * RAD_TO_DEG * 100);
			current_angle = (current_angle < frame->min_step) ? frame->min_step : current_angle;
			frame->offset = frame->offset - current_angle;
		}
	}
}
