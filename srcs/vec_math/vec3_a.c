/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:39:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/25 08:50:01 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xyz	vec3(float x, float y, float z)
{
	float	w;

	w = 1.0f;
	return ((t_xyz){x, y, z, w});
}

t_xyz	vec3_add(t_xyz a, t_xyz b)
{
	return ((t_xyz){a.x + b.x, a.y + b.y, a.z + b.z, 1.0f});
}

t_xy	vec3_to_vec2(t_xyz a)
{
	return ((t_xy){a.x, a.y});
}

float	vec3_eucl_dist(t_xyz a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_xyz	inv_z(t_xyz a)
{
	a.z = 1.0f / a.z;
	a.x = a.x * a.z;
	a.y = a.y * a.z;
	return (a);
}

t_uvz	texel_inv_z(t_uvz a)
{
	a.z = 1.0f / a.z;
	a.u = a.u * a.z;
	a.v = a.v * a.z;
	return (a);
}
