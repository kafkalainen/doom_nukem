/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_g.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 11:39:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/09 13:30:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	calc_texel(t_uvz *texel, t_uvz *start, float offset,
					t_uvz *end)
{
	texel->u = (1.0f - offset) * start->u + offset * end->u;
	texel->v = (1.0f - offset) * start->v + offset * end->v;
	texel->w = (1.0f - offset) * start->w + offset * end->w;
}

void	calc_lumel(float *lumel, float *start, float offset, float *end)
{
	*lumel = (1.0f - offset) * *start + offset * *end;
}

t_bool	vec3_is_inside_triangle(t_triangle *tri, t_xyz point)
{
	if (vec3_check_sidedness(point, tri->p[0], tri->p[1], tri->p[2])
		&& vec3_check_sidedness(point, tri->p[1], tri->p[0], tri->p[2])
		&& vec3_check_sidedness(point, tri->p[2], tri->p[0], tri->p[1]))
	{
		return (true);
	}
	return (false);
}

t_bool	vec3_check_sidedness(t_xyz p1, t_xyz p2, t_xyz a, t_xyz b)
{
	t_xyz	cross_products[2];

	cross_products[0] = vec3_unit_vector(vec3_cross_product(
				vec3_dec(b, a), vec3_dec(p1, a)));
	cross_products[1] = vec3_unit_vector(vec3_cross_product(
				vec3_dec(b, a), vec3_dec(p2, a)));
	if (vec3_dot_product(cross_products[0], cross_products[1]) < 0.00001f)
		return (false);
	else
		return (true);
}

/*
**	First we test, if ray is parallel to the plane.
**	If first dotproduct is less than zero, triangle is behind.
**	Point of intersection is then the direction * barycentric
**	coordinate multiplier. We test the sidedness of new triangle,
**	and calculate it's vectors along the edges, if any point
**	lies outside any of it's edges, then we return false.
*/
t_bool	vec3_ray_triangle_intersect(t_triangle *tri, t_xyz pos, t_xyz dir,
		t_xyz *isection)
{
	float	dot;
	t_plane	plane;

	plane.point = tri->p[0];
	plane.normal = tri->normal;
	*isection = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
	dot = vec3_dot_product(vec3_unit_vector(vec3_dec(*isection, pos)), dir);
	if (dot > 0.0f && vec3_is_inside_triangle(tri, *isection))
	{
		return (true);
	}
	return (false);
}
