/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:06:01 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/05 09:06:44 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xyz	vec3_dec(t_xyz a, t_xyz b)
{
	t_xyz	dec;

	dec.x = a.x - b.x;
	dec.y = a.y - b.y;
	dec.z = a.z - b.z;
	dec.w = 1.0f;
	return (dec);
}

t_xyz	vec3_cross_product(t_xyz a, t_xyz b)
{
	t_xyz	cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	cross.w = 1.0f;
	return (cross);
}

t_xyz	triangle_normal(t_triangle *triangle)
{
	t_xyz	p0p1;
	t_xyz	p0p2;
	t_xyz	normal;
	float	magnitude;

	p0p1 = vec3_dec(triangle->p[1], triangle->p[0]);
	p0p2 = vec3_dec(triangle->p[2], triangle->p[0]);
	normal = vec3_cross_product(p0p1, p0p2);
	magnitude = 1.0f / vec3_eucl_dist(normal);
	normal.x = normal.x * magnitude;
	normal.y = normal.y * magnitude;
	normal.z = normal.z * magnitude;
	normal.w = 0.0f;
	return (normal);
}

t_xyz	vec3_unit_vector(t_xyz a)
{
	float	magnitude;

	magnitude = vec3_eucl_dist(a);
	magnitude = 1 / magnitude;
	return ((t_xyz){a.x * magnitude, a.y * magnitude, a.z * magnitude, 1.0f});
}

float	vec3_dot_product(t_xyz a, t_xyz b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
