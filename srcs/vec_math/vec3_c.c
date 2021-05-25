/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:04:51 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/25 09:29:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_uvz	uvz_calculate_value_with_delta(float delta_x, t_uvz delta_u, t_uvz delta_v)
{
	t_uvz	value;

	value.z = delta_x * delta_u.z + delta_v.z;
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
