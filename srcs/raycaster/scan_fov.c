/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 07:59:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/22 10:57:18 by jnivala          ###   ########.fr       */
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

static void		ft_draw_wall(t_xy left, t_xy right, t_frame *frame, float current_pxl, int color, t_home *home, t_player *plr)
{
	float		screen_wall;
	float		screen_offset;
	float		wall_height_left;
	float		wall_height_right;
	float		step;
	float		z_step;
	float		angle_mult;
	int			i;

	i = 0;
	// if (right.x < 0)
	// {
	// 	right.y = ft_interpolate_y(left, right);
	// 	right.x = 0;
	// 	current_angle = vec2_angle(left, right);
	// }
	screen_wall = current_pxl;
	z_step = get_distance(plr->pos, left) / get_distance(plr->pos, right);
	screen_offset = SCREEN_WIDTH - frame->offset;
	wall_height_left = 480 / (fabs(left.x + left.y) * SQR2) * 20;
	wall_height_right = 480 / (fabs(right.x + right.y) * SQR2) * 20;
	step = (wall_height_left - wall_height_right) / screen_wall;
	angle_mult = angle_offset(current_pxl, screen_offset, screen_wall);
	while (i < (int)screen_wall)
	{
		ft_draw_line(
			vec2(screen_offset + i, plr->pitch - wall_height_left),
			vec2(screen_offset + i, plr->pitch + wall_height_left),
			color,
			frame->draw_surf);
		wall_height_left = wall_height_left - step;
		z_step -= screen_wall * z_step;
		i++;
	}
}

static float	round_angle(float angle, float *pxl_offset)
{
	float			angle_as_pixels;
	int				trunc;

	angle_as_pixels = angle / 0.002454369f;
	trunc = (int)angle_as_pixels;
	*pxl_offset = angle_as_pixels - trunc + *pxl_offset;
	if (*pxl_offset >= 1.0f)
	{
		*pxl_offset = *pxl_offset - 1.0f;
		return ((float)(trunc + 1.0f));
	}
	else
		return ((float)trunc);
}

int				check_if_same_wall(t_xy a, t_xy b, t_xy right_point)
{
	if (a.x == b.x && a.y == b.y)
	{
		if (right_point.x != -1 && right_point.y != -1)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

void			scan_fov(t_home *home, t_frame *frame, t_player *plr)
{
	t_ray_fov	fov_left;
	t_ray_fov	fov_right;
	t_frame		new_frame;
	int			current_pxl;

	current_pxl = 0;
	fov_left.left_point = vec2(-1,-1);
	fov_right.right_point = vec2(-1,-1);
	fov_left.wall = home->sectors[frame->idx]->points;
	fov_right.wall = home->sectors[frame->idx]->points;
	continue_from_last_sector(fov_left.wall, &fov_left, frame);
	get_left_point(fov_left.wall, &fov_left, frame, home->sectors[frame->idx]->nb_of_walls);
	get_right_point(fov_left.wall, &fov_right, frame, home->sectors[frame->idx]->nb_of_walls);
	draw_text(home, ft_ftoa(plr->z, 2, 1), frame, vec2(32, 32));
	while (frame->offset > frame->max_fov)
	{
		if (current_pxl != 0)
			continue_from_next_point(fov_left.wall, &fov_left, frame);
		if (check_if_same_wall(fov_left.wall->x0, fov_right.wall->x0, fov_right.right_point))
			fov_left.right_point = fov_right.right_point;
		current_pxl = round_angle(vec2_angle(fov_left.left_point, fov_left.right_point), &frame->pxl_offset);
		if (check_if_portal(fov_left.wall, frame) && !check_if_same_point(current_pxl, &fov_left))
		{
			current_pxl++;
			setup_frame(frame, &new_frame, current_pxl, fov_left.wall->idx);
			scan_fov(home, &new_frame, plr);
			frame->offset = new_frame.offset;
			frame->pxl_offset = new_frame.pxl_offset;
		}
		else
		{
			ft_draw_wall(fov_left.left_point, fov_left.right_point, frame, current_pxl, 0xFF8000 + get_distance(fov_left.left_point, fov_right.right_point) * 100, home, plr);
			ft_draw_line(
				vec2_add(fov_left.left_point, home->offset),
				vec2_add(fov_left.right_point, home->offset),
				green,
				frame->draw_surf);
			current_pxl++;
			frame->offset = frame->offset - current_pxl;
		}
	}
}