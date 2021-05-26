/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:04:51 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/26 16:06:45 by jnivala          ###   ########.fr       */
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

t_xyz	vec3_intersection_with_plane(t_xyz plane_p, t_xyz plane_n, t_xyz start,
	t_xyz end, float *texel_offset)
{
		float	plane_distance;
		float	start_distance;
		float	end_distance;
		t_xyz	line_to_plane;
		t_xyz	line;

		plane_n = vec3_unit_vector(plane_n);
		plane_distance = -vec3_dot_product(plane_n, plane_p);
		start_distance = vec3_dot_product(start, plane_n);
		end_distance = vec3_dot_product(end, plane_n);
		*texel_offset = interpolate_points(start_distance, -plane_distance,
			start_distance, end_distance);
		line = vec3_dec(start, end);
		line_to_plane = vec3_mul(line, *texel_offset);
		return (vec3_add(start, line_to_plane));
}
