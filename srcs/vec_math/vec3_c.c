/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:04:51 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/05 11:14:14 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_uvz	uvz_calculate_value_with_delta(float delta_x, t_uvz delta_u,
	t_uvz delta_v)
{
	t_uvz	value;

	value.w = delta_x * delta_u.w + delta_v.w;
	value.u = delta_x * delta_u.u + delta_v.u;
	value.v = delta_x * delta_u.v + delta_v.v;
	return (value);
}

float	triangle_calculate_average_z(t_triangle *triangle)
{
	return ((triangle->p[0].z + triangle->p[1].z + triangle->p[2].z) / 3.0f);
}

t_xyz	vec3_mul(t_xyz a, float scalar)
{
	return ((t_xyz){a.x * scalar, a.y * scalar, a.z * scalar, 1.0f});
}

t_xyz	vec3_div(t_xyz a, float scalar)
{
	return ((t_xyz){a.x / scalar, a.y / scalar, a.z / scalar, 1.0f});
}

/*
**	vec3_unit_vector ok.
**	vec3_dot_product ok.
**	swapped end with start on line 65 vec3_dec call -> fixed error.
**	added pointer to plane.
**	function should handle special cases as well,
**	there is an error when clipping to near plane.
**	testing to return plane->point when we are clipping
**	to near plane, no more hanging.
*/
t_xyz	vec3_intersection_with_plane(t_plane *plane, t_xyz start, t_xyz end,
	float *texel_offset)
{
	float	plane_dot;
	float	start_dot;
	float	end_dot;
	t_xyz	line_to_plane;
	t_xyz	line;

	if (vec3_dot_product(vec3_dec(end, start), plane->normal) == 0)
		return (end);
	plane->normal = vec3_unit_vector(plane->normal);
	plane_dot = -vec3_dot_product(plane->normal, plane->point);
	start_dot = vec3_dot_product(start, plane->normal);
	end_dot = vec3_dot_product(end, plane->normal);
	if (start_dot == end_dot)
		return (plane->point);
	*texel_offset = interpolate_points(start_dot, -plane_dot,
			start_dot, end_dot);
	line = vec3_dec(end, start);
	line_to_plane = vec3_mul(line, *texel_offset);
	return (vec3_add(start, line_to_plane));
}
