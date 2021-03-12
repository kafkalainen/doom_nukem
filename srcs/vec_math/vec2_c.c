/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:14:05 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/12 16:06:53 by jnivala          ###   ########.fr       */
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
	a.x = a.x / a.z;
	a.y = a.y / a.z;
	a.z = 1.0f / a.z;
	return (a);
}

float	vec2_to_screen_space(float x, float z)
{
	return (SCREEN_WIDTH - ((SCREEN_HEIGHT / z) * x) + 15);
}
