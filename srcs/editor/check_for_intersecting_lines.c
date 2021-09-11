/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_intersecting_lines.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 08:58:12 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/11 15:20:42 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	editor_point_is_on_the_lseg(t_screen_xy a,
			t_screen_xy c, t_screen_xy b)
{
	t_xy	vec_ab;
	t_xy	vec_ac;
	float	dot_ab_ab;
	float	dot_ab_ac;

	vec_ab = vec2_dec(vec2(b.x, b.y), vec2(a.x, a.y));
	vec_ac = vec2_dec(vec2(c.x, c.y), vec2(a.x, a.y));
	if (vec2_cross(vec_ab, vec_ac) != 0)
		return (false);
	dot_ab_ab = vec2_dot(vec_ab, vec_ab);
	dot_ab_ac = vec2_dot(vec_ab, vec_ac);
	if (dot_ab_ac > 0 && dot_ab_ac < dot_ab_ab)
		return (true);
	else
		return (false);
}

int	editor_orientation_of_three_points(t_screen_xy a,
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

t_bool	editor_check_if_lseg_intersects(t_editor_walls *wall,
				t_screen_xy pos, t_screen_xy dir)
{
	int	or[4];

	or[0] = editor_orientation_of_three_points(wall->x0,
			wall->next->x0, pos);
	or[1] = editor_orientation_of_three_points(wall->x0,
			wall->next->x0, dir);
	or[2] = editor_orientation_of_three_points(pos, dir, wall->x0);
	or[3] = editor_orientation_of_three_points(pos, dir, wall->next->x0);
	if (or[0] != or[1] && or[2] != or[3])
		return (true);
	if (or[0] == colinear && editor_point_is_on_the_lseg(wall->x0, pos,
			wall->next->x0))
		return (true);
	if (or[1] == colinear && editor_point_is_on_the_lseg(wall->x0, dir,
			wall->next->x0))
		return (true);
	if (or[2] == colinear && editor_point_is_on_the_lseg(pos, wall->x0, dir))
		return (true);
	if (or[3] == colinear && editor_point_is_on_the_lseg(pos, wall->next->x0,
			dir))
		return (true);
	return (false);
}

t_bool	editor_check_if_same_point(t_screen_xy p0, t_screen_xy p1)
{
	if (p0.x == p1.x && p0.y == p1.y)
		return (true);
	else
		return (false);
}

t_bool	check_for_intersecting_lines(t_editor_sector *sector,
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
			if (!editor_check_if_same_point(p0, temp->next->x0)
				&& !editor_check_if_same_point(p0, temp->x0)
				&& !editor_check_if_same_point(p1, temp->next->x0)
				&& !editor_check_if_same_point(p1, temp->x0))
			{
				if (editor_check_if_lseg_intersects(temp, p0, p1))
					return (true);
			}
		}
		temp = temp->next;
		i++;
	}
	return (false);
}
