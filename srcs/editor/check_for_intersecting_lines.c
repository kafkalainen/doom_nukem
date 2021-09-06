/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_intersecting_lines.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 08:58:12 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/02 21:11:11 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static int	point_is_on_the_lseg(t_screen_xy a, t_screen_xy c, t_screen_xy b)
{
	t_xy	vec_ab;
	t_xy	vec_ac;
	float	dot_ab_ab;
	float	dot_ab_ac;

	vec_ab = vec2_dec((t_xy){b.x, b.y, 1.0f}, (t_xy){a.x, a.y, 1.0f});
	vec_ac = vec2_dec((t_xy){c.x, c.y, 1.0f}, (t_xy){a.x, a.y, 1.0f});
	if (vec2_cross(vec_ab, vec_ac) != 0)
		return (0);
	dot_ab_ab = vec2_dot(vec_ab, vec_ab);
	dot_ab_ac = vec2_dot(vec_ab, vec_ac);
	if (dot_ab_ac > 0 && dot_ab_ac < dot_ab_ab)
		return (1);
	else
		return (0);
}

static int	orientation_of_three_points(t_screen_xy a,
			t_screen_xy b, t_screen_xy c)
{
	float	slope;

	slope = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
	if (slope == 0)
		return (colinear);
	if (slope > 0)
		return (clockwise);
	else
		return (c_clockwise);
}

static int	editor_check_if_lseg_intersects(t_editor_walls *wall,
			t_screen_xy pos, t_screen_xy dir)
{
	int		pos_orientation;
	int		dir_orientation;
	int		p0_orientation;
	int		p1_orientation;

	pos_orientation = orientation_of_three_points(wall->x0,
			wall->next->x0, pos);
	dir_orientation = orientation_of_three_points(wall->x0,
			wall->next->x0, dir);
	p0_orientation = orientation_of_three_points(pos, dir, wall->x0);
	p1_orientation = orientation_of_three_points(pos, dir, wall->next->x0);
	if (pos_orientation != dir_orientation
		&& p0_orientation != p1_orientation)
		return (1);
	if (pos_orientation == 0
		&& point_is_on_the_lseg(wall->x0, pos, wall->next->x0))
		return (1);
	if (dir_orientation == 0
		&& point_is_on_the_lseg(wall->x0, dir, wall->next->x0))
		return (1);
	if (p0_orientation == 0 && point_is_on_the_lseg(pos, wall->x0, dir))
		return (1);
	if (p1_orientation == 0 && point_is_on_the_lseg(pos, wall->next->x0, dir))
		return (1);
	return (0);
}

static int	check_if_same_point(t_screen_xy p0, t_screen_xy p1)
{
	if (p0.x == p1.x && p0.y == p1.y)
		return (1);
	else
		return (0);
}

int	check_for_intersecting_lines(t_sector_list *sector,
	t_screen_xy p0, t_screen_xy p1)
{
	int				i;
	t_editor_walls	*temp;

	i = 0;
	temp = sector->walls;
	if (sector->nb_of_walls < 1)
		return (0);
	while (i < sector->nb_of_walls)
	{
		if (temp && temp->next)
		{
			if (!check_if_same_point(p0, temp->next->x0)
				&& !check_if_same_point(p0, temp->x0)
				&& !check_if_same_point(p1, temp->next->x0)
				&& !check_if_same_point(p1, temp->x0))
			{
				if (editor_check_if_lseg_intersects(temp, p0, p1))
					return (1);
			}
		}
		temp = temp->next;
		i++;
	}
	return (0);
}
