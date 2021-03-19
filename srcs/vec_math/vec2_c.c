/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:14:05 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/19 09:39:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

float	vec2_perp_dist(t_xy a)
{
	return (fabsf(a.x + a.y) * SQR2);
}

t_xyz	vec3_add(t_xyz a, t_xyz b)
{
	return ((t_xyz){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_xyz	vec3(float x, float y, float z)
{
	return ((t_xyz){x, y, z});
}

t_xyz	inv_z(t_xyz a)
{
	a.z = 1.0f / a.z;
	a.x = a.x * a.z;
	a.y = a.y * a.z;
	return (a);
}

float	vec2_to_screen_space(float x, float z)
{
	return (SCREEN_WIDTH - ((SCREEN_HEIGHT / z) * x) + 15);
}

float	interpolate_points(float x0, float x1, float y0, float y1)
{
	return ((x1 - x0) / (y1 - y0));
}

t_xy	vec3_to_vec2(t_xyz a)
{
	return ((t_xy){a.x, a.y});
}
