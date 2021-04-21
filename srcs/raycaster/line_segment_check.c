/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_segment_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 10:03:40 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/21 16:53:00 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
** Point is not in the wall calculation checks that are two vectors colinear.
** If they are not, then the point cannot be in the wall.
** If they are, we check the dot product. If dot product of ab and ac is
** greater than zero and dot product of ac is less than ab, then the point
** is on the wall.
*/

int	point_is_on_the_lseg(t_xy a, t_xy c, t_xy b)
{
	t_xy	vec_ab;
	t_xy	vec_ac;
	float	dot_ab_ab;
	float	dot_ab_ac;

	vec_ab = vec2_dec(b, a);
	vec_ac = vec2_dec(c, a);
	if (vec2_cross(vec_ab, vec_ac) != 0)
		return (0);
	dot_ab_ab = vec2_dot(vec_ab, vec_ab);
	dot_ab_ac = vec2_dot(vec_ab, vec_ac);
	if (dot_ab_ac > 0 && dot_ab_ac < dot_ab_ab)
		return (1);
	else
		return (0);
}

int	orientation_of_three_points(t_xy a, t_xy b, t_xy c)
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

int	check_if_lseg_intersects(t_point *p0, t_xy *pos, t_xy *dir)
{
	int		pos_orientation;
	int		dir_orientation;
	int		p0_orientation;
	int		p1_orientation;

	pos_orientation = orientation_of_three_points(p0->x0, p0->next->x0, *pos);
	dir_orientation = orientation_of_three_points(p0->x0, p0->next->x0, *dir);
	p0_orientation = orientation_of_three_points(*pos, *dir, p0->x0);
	p1_orientation = orientation_of_three_points(*pos, *dir, p0->next->x0);
	if (pos_orientation != dir_orientation && p0_orientation != p1_orientation)
		return (1);
	if (pos_orientation == 0
		&& point_is_on_the_lseg(p0->x0, *pos, p0->next->x0))
		return (1);
	if (dir_orientation == 0
		&& point_is_on_the_lseg(p0->x0, *dir, p0->next->x0))
		return (1);
	if (p0_orientation == 0 && point_is_on_the_lseg(*pos, p0->x0, *dir))
		return (1);
	if (p1_orientation == 0 && point_is_on_the_lseg(*pos, p0->next->x0, *dir))
		return (1);
	return (0);
}
