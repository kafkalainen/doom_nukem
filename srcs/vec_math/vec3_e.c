/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_e.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 11:36:24 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/10 13:29:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	vec3_signed_distance_to_plane(t_xyz point, t_xyz plane_normal,
	t_xyz plane_point)
{
	float	d;

	d = vec3_dot_product(vec3_dec(point, plane_point), plane_normal);
	if (d <= 0)
		return (1);
	else
		return (0);
}

float	area_of_triangle(t_xyz p0, t_xyz p1, t_xyz p2)
{
	return (fabsf((p0.x * (p1.z - p2.z)
				+ p1.x * (p2.z - p0.z)
				+ p2.x * (p0.z - p1.z)) / 2.0f));
}

Uint32	point_inside_a_triangle(t_xyz p1, t_xyz p2, t_xyz p3, t_xyz p)
{
	float	area;
	float	area1;
	float	area2;
	float	area3;

	area = area_of_triangle(p1, p2, p3);
	area1 = area_of_triangle(p, p2, p3);
	area2 = area_of_triangle(p1, p, p3);
	area3 = area_of_triangle(p1, p2, p);
	if (area == area1 + area2 + area3)
		return (TRUE);
	else
		return (FALSE);
}

t_xyz	vec3_intersection_with_ray_and_plane(t_plane *plane, t_xyz origo, t_xyz dir)
{
	float	t;
	float	denom;

	t = vec3_dot_product(vec3_dec(plane->point, origo), plane->normal);
	denom = vec3_dot_product(dir, plane->normal);
	if (denom == 0)
		return (origo);
	t = t / denom;
	return (vec3_add(origo, vec3_mul(dir, t)));
}
