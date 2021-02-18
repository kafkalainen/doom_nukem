/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 07:59:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/18 12:33:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"


static float	ft_interpolate_y(t_xy p0, t_xy p1)
{
	if (p1.x - p0.x == 0)
		return (p1.y - p0.y);
	return (p0.y + (0 - p0.x) * ((p1.y - p0.y) / (p1.x - p0.x)));
}

static float	angle_offset(float current_angle, float screen_offset, float screen_wall)
{
	float		angle_mult_left;
	float		angle_mult_right;
	float		euc_offset;

	euc_offset = screen_offset >= 320 ? screen_offset - 320 : screen_offset;
	angle_mult_left = FOV - euc_offset * .00178373853125f;
	angle_mult_right = FOV - (euc_offset + screen_wall) * .00178373853125f;
	return ((angle_mult_left - angle_mult_right) / screen_wall);
}

/*
** Almost working. only issue is a very small correction error on left/right near walls.
** Curved walls: wall_height_left = wall_height_left - step + i * 0.0012944174;
** Angle does not work.
*/
static void		ft_draw_wall(t_xy left, t_xy right, t_frame *frame, float current_angle, int color, t_home *home)
{
	float		screen_wall;
	float		screen_offset;
	float		wall_height_left;
	float		wall_height_right;
	float		step;
	float		angle_mult;
	int			i;

	i = 0;
	if (right.x < 0)
	{
		right.y = ft_interpolate_y(left, right);
		right.x = 0;
		current_angle = vec2_angle(left, right);
	}
	screen_wall = SCREEN_WIDTH / FOV * current_angle;
	screen_offset = SCREEN_WIDTH / FOV * (FOV - frame->offset);
	wall_height_left = 480 / (fabs(left.x + left.y)) * 20;
	wall_height_right = 480 / (fabs(right.x + right.y)) * 20;
	step = (wall_height_left - wall_height_right) / screen_wall;
	angle_mult = angle_offset(current_angle, screen_offset, screen_wall);
	while (i < (int)screen_wall)
	{
		ft_draw_line(
			vec2(screen_offset + i, 240 - wall_height_left),
			vec2(screen_offset + i, 240 + wall_height_left),
			color,
			frame->draw_surf);
		wall_height_left = wall_height_left - step;
		i++;
	}
}

static float	round_angle(float angle)
{
	static float	temp = 0.0f;
	int				trunc;

	angle /= .002454369f;
	trunc = angle;
	// if (temp != 0.0f)
	// 	temp += angle - trunc;
	// else
	// 	temp = angle - trunc;
	// if (temp > 1.0f)
	// {
	// 	temp = temp - 1.0f;
	// 	return ((float)(trunc + 1.0f) * .002454369f);
	// }
	// else
		return ((float)trunc * .002454369f);
}

int				check_if_same_wall(t_xy a, t_xy b)
{
	if (a.x == b.x && a.y == b.y)
		return (1);
	else
		return (0);
}

void			scan_fov(t_home *home, t_frame *frame)
{
	t_ray_fov	fov;
	t_ray_fov	fov2;
	t_frame		new_frame;
	float		current_angle;

	current_angle = 0.0f;
	fov.left_point = vec2(-1,-1);
	fov2.right_point = vec2(-1,-1);
	fov.left_wall = home->sectors[frame->idx]->points;
	fov2.left_wall = home->sectors[frame->idx]->points;
	continue_from_last_sector(fov.left_wall, &fov, frame);
	get_left_point(fov.left_wall, &fov, frame, home->sectors[frame->idx]->nb_of_walls);
	get_right_point(fov.left_wall, &fov2, frame, home->sectors[frame->idx]->nb_of_walls);
	while (frame->offset > frame->max_fov)
	{
		if (current_angle != 0)
			continue_from_next_point(fov.left_wall, &fov, frame);
		if (check_if_same_wall(fov.left_wall->x0, fov2.left_wall->x0))
			fov.right_point = fov2.right_point;
		current_angle = vec2_angle(fov.left_point, fov.right_point);
		draw_rect_center(vec2_add(fov.left_point, home->offset), vec2(8, 8), frame);
		draw_rect_center(vec2_add(fov2.right_point, home->offset), vec2(8, 8), frame);
		if (check_if_portal(fov.left_wall, frame) && !check_if_same_point(current_angle, &fov))
		{
			current_angle += frame->min_step;
			setup_frame(frame, &new_frame, current_angle, fov.left_wall->idx);
			scan_fov(home, &new_frame);
			frame->offset = new_frame.offset + frame->min_step;
		}
		else
		{
			ft_draw_wall(fov.left_point, fov.right_point, frame, current_angle, 0xFF8000 + frame->offset * RAD_TO_DEG * 100, home);
			ft_draw_line(
				vec2_add(fov.left_point, home->offset),
				vec2_add(fov.right_point, home->offset),
				green,
				frame->draw_surf);
			current_angle += frame->min_step;
			frame->offset = frame->offset - current_angle;
		}
	}
}
