/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 07:59:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/11 17:28:57 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"


static float	ft_interpolate_y(t_xy p0, t_xy p1)
{
	if (p1.x - p0.x == 0)
		return (p1.y - p0.y);
	return (p0.y + (0 - p0.x) * ((p1.y - p0.y) / (p1.x - p0.x)));
}

/*
**
** Almost working. only issue is a very small correction error on left/right near walls.
** Curved walls: wall_height_left = wall_height_left - step + i * 0.0012944174;
*/
static void		ft_draw_wall(t_xy left, t_xy right, t_frame *frame, float current_angle, int color, t_home *home)
{
	float		screen_wall;
	float		screen_offset;
	float		euc_offset;
	float		wall_height_left;
	float		wall_height_right;
	float		distance_left;
	float		distance_right;
	float		diff;
	float		step;
	float		angle_mult_left;
	float		angle_mult_right;
	int			i;

	if (right.x < 0)
	{
		right.y = ft_interpolate_y(left, right);
		right.x = 0;
		current_angle = vec2_angle(left, right);
	}
	i = 0;
	screen_wall = SCREEN_WIDTH / FOV * current_angle;
	screen_offset = SCREEN_WIDTH / FOV * (FOV - frame->offset);
	draw_text(home, ft_ftoa(screen_offset, 5, 1), frame, vec2(screen_offset, 140));
	draw_text(home, ft_ftoa(screen_wall, 5, 1), frame, vec2(screen_offset, 180));
	euc_offset = screen_offset >= 320 ? screen_offset - 320 : screen_offset;
	angle_mult_left = 1.4142135624 - euc_offset * .0012944174;
	angle_mult_right = 1.4142135624 - (euc_offset + screen_wall) * .0012944174;
	distance_left = vec2_mag(left);
	distance_right = vec2_mag(right);
	wall_height_left = 480 / (fabs(left.x + left.y)) * 20;
	wall_height_right = 480 / (fabs(right.x + right.y)) * 20;
	diff = wall_height_left - wall_height_right;
	step = diff / screen_wall;
	// draw_text(home, ft_ftoa(wall_height_left, 5, 1), frame, vec2(screen_offset, 420));
	// draw_text(home, ft_ftoa(wall_height_right, 5, 1), frame, vec2(screen_offset + screen_wall, 450));
	angle_mult_left -= angle_mult_right;
	angle_mult_left /= screen_wall; 
	while (i < (int)screen_wall)
	{
		draw_horizon(
			vec2(screen_offset + i, 240 - wall_height_left),
			vec2(screen_offset + i, 240 + wall_height_left),
			color,
			frame->draw_surf);
		wall_height_left = wall_height_left - step + angle_mult_left;
		i++;
	}
}

void			calc_perp_wall(t_xy left, t_xy right, float current_angle, t_frame *frame, t_home *home)
{
	float	perp_left_dist;
	float	perp_right_dist;
	float	eucl_left_dist;
	float	eucl_right_dist;

	if (right.x < 0)
	{
		right.y = ft_interpolate_y(left, right);
		right.x = 0;
	}
	eucl_left_dist = vec2_mag(left);
	eucl_right_dist = vec2_mag(right);
	perp_left_dist = fabs(left.x + left.y) / 1.4142135624;
	perp_right_dist = fabs(right.x + right.y) / 1.4142135624;
	draw_text(home, ft_ftoa(perp_left_dist, 5, 1), frame, vec2_add(left, home->offset));
	draw_text(home, ft_ftoa(perp_right_dist, 5, 1), frame, vec2_add(right, home->offset));
	// draw_text(home, ft_ftoa(eucl_left_dist, 5, 1), frame, vec2_add(home->offset, vec2(left.x, -100)));
	draw_text(home, ft_ftoa(eucl_right_dist, 5, 1), frame, vec2_add(home->offset, vec2(right.x, -100)));
}

int				draw_horizon(t_xy start, t_xy end, int color, SDL_Surface *surf)
{
	t_xy	length;
	t_xy	ratio;
	int		pixels;
	t_xy	pos;

	length = vec2(fabs(end.x - start.x), fabs(end.y - start.y));
	pixels = (length.x > length.y) ? (length.x) : (length.y);
	ratio.x = (start.y != end.y) ? (length.x / length.y) : 1;
	ratio.y = (start.x != end.x) ? (length.y / length.x) : 1;
	ratio.x = (ratio.x > ratio.y) ? 1 : (ratio.x);
	ratio.y = (ratio.y > ratio.x) ? 1 : (ratio.y);
	pos.x = start.x;
	pos.y = start.y;
	while (pixels-- > 0)
	{
		if (pos.x >= 0 && pos.x < SCREEN_WIDTH && pos.y >= 0 && pos.y < SCREEN_HEIGHT)
			put_pixel(surf, pos.x, pos.y, color);
		pos.x += ratio.x * ((start.x < end.x) ? 1 : -1);
		pos.y += ratio.y * ((start.y < end.y) ? 1 : -1);
	}
	return (TRUE);
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
			ft_draw_wall(fov.left_point, fov.right_point, frame, current_angle, 0xFF8000 + frame->offset * RAD_TO_DEG * 100, home);
			current_angle = (current_angle < frame->min_step) ? frame->min_step : current_angle;
			frame->offset = frame->offset - current_angle;
		}
	}
}
