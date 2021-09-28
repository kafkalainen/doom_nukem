/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_e.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 11:36:24 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/28 14:46:36 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float	vec3_signed_distance_to_plane(t_xyz point, t_xyz plane_normal,
	t_xyz plane_point)
{
	float	d;

	d = vec3_dot_product(vec3_dec(point, plane_point), plane_normal);
	return (d);
}

float	area_of_triangle(t_xyz p0, t_xyz p1, t_xyz p2)
{
	return (fabsf((p0.x * (p1.z - p2.z)
				+ p1.x * (p2.z - p0.z)
				+ p2.x * (p0.z - p1.z)) / 2.0f));
}

t_bool	point_inside_a_triangle_surface(t_xyz p0, t_xyz p1, t_xyz p2, t_xyz p)
{
	float	plane_p0p1;
	float	plane_p1p2;
	float	plane_p2p0;

	plane_p0p1 = (p0.x - p.x) * (p1.z - p.z) - (p1.x - p.x) * (p0.z - p.z);
	plane_p1p2 = (p1.x - p.x) * (p2.z - p.z) - (p2.x - p.x) * (p1.z - p.z);
	plane_p2p0 = (p2.x - p.x) * (p0.z - p.z) - (p0.x - p.x) * (p2.z - p.z);
	plane_p0p1 = ft_signf(plane_p0p1);
	plane_p1p2 = ft_signf(plane_p1p2);
	plane_p2p0 = ft_signf(plane_p2p0);
	if (plane_p0p1 == plane_p1p2 && plane_p1p2 == plane_p2p0)
		return (true);
	else
		return (false);
}

t_xyz	vec3_intersection_with_ray_and_plane(t_plane *plane, t_xyz origo,
		t_xyz dir)
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

void	triangle_div(t_triangle *projected)
{
	projected->p[0] = vec3_div(projected->p[0], projected->p[0].w);
	projected->p[1] = vec3_div(projected->p[1], projected->p[1].w);
	projected->p[2] = vec3_div(projected->p[2], projected->p[2].w);
}
