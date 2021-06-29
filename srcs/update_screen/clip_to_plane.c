/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_to_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 11:58:40 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/29 11:53:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	check_if_inside_triangle(float d, t_point_location *loc,
	t_triangle *src, Uint32 i)
{
	if (d >= 0.0f)
	{
		loc->texels_inside[loc->inside] = src->uv[i];
		loc->points_inside[loc->inside] = src->p[i];
		loc->lumels_inside[loc->inside] = src->lu[i];
		loc->inside += 1;
	}
	else
	{
		loc->texels_outside[loc->outside] = src->uv[i];
		loc->points_outside[loc->outside] = src->p[i];
		loc->lumels_outside[loc->outside] = src->lu[i];
		loc->outside += 1;
	}
}

static t_uvz	calculate_texel_offset(t_uvz from, t_uvz to, float t)
{
	t_uvz	sum;

	sum.u = t * (to.u - from.u) + from.u;
	sum.v = t * (to.v - from.v) + from.v;
	sum.w = t * (to.w - from.w) + from.w;
	return (sum);
}

static float	calculate_lumel_offset(float from, float to, float t)
{
	float	sum;

	sum = t * (to - from) + from;
	return (sum);
}

static int	form_a_triangle(t_point_location *loc, t_plane *plane,
	t_triangle *triangle1)
{
	triangle1->p[0] = loc->points_inside[0];
	triangle1->uv[0] = loc->texels_inside[0];
	triangle1->lu[0] = loc->lumels_inside[0];
	triangle1->p[1] = vec3_intersection_with_plane(plane, loc->points_inside[0],
			loc->points_outside[0], &loc->texel_offset);
	triangle1->uv[1] = calculate_texel_offset(loc->texels_inside[0],
			loc->texels_outside[0], loc->texel_offset);
	triangle1->lu[1] = calculate_lumel_offset(loc->lumels_inside[0],
		loc->lumels_outside[0], loc->texel_offset);
	triangle1->p[2] = vec3_intersection_with_plane(plane, loc->points_inside[0],
			loc->points_outside[1], &loc->texel_offset);
	triangle1->uv[2] = calculate_texel_offset(loc->texels_inside[0],
			loc->texels_outside[1], loc->texel_offset);
	triangle1->lu[2] = calculate_lumel_offset(loc->lumels_inside[0],
		loc->lumels_outside[1], loc->texel_offset);
	return (1);
}

static int	form_a_quadrant(t_point_location *loc, t_plane *plane,
	t_triangle *triangle1, t_triangle *triangle2)
{
	triangle1->p[0] = loc->points_inside[0];
	triangle1->uv[0] = loc->texels_inside[0];
	triangle1->lu[0] = loc->lumels_inside[0];
	triangle1->p[1] = loc->points_inside[1];
	triangle1->uv[1] = loc->texels_inside[1];
	triangle1->lu[1] = loc->lumels_inside[1];
	triangle1->p[2] = vec3_intersection_with_plane(plane, loc->points_inside[0],
			loc->points_outside[0], &loc->texel_offset);
	triangle1->uv[2] = calculate_texel_offset(loc->texels_inside[0],
			loc->texels_outside[0], loc->texel_offset);
	triangle1->lu[2] = calculate_lumel_offset(loc->lumels_inside[0],
		loc->lumels_outside[0], loc->texel_offset);
	triangle2->p[0] = loc->points_inside[1];
	triangle2->uv[0] = loc->texels_inside[1];
	triangle2->lu[0] = loc->lumels_inside[1];
	triangle2->p[1] = triangle1->p[2];
	triangle2->uv[1] = triangle1->uv[2];
	triangle2->lu[1] = triangle1->lu[2];
	triangle2->p[2] = vec3_intersection_with_plane(plane, loc->points_inside[1],
			loc->points_outside[0], &loc->texel_offset);
	triangle2->uv[2] = calculate_texel_offset(loc->texels_inside[1],
			loc->texels_outside[0], loc->texel_offset);
	triangle2->lu[2] = calculate_lumel_offset(loc->lumels_inside[1],
		loc->lumels_outside[0], loc->texel_offset);
	return (2);
}

int	clip_against_plane(t_plane *plane, t_triangle *src,
		t_triangle *triangle1, t_triangle *triangle2)
{
	t_point_location	loc;
	float				d[3];

	initialize_locations(&loc);
	plane->normal = vec3_unit_vector(plane->normal);
	d[0] = vec3_dot_product(plane->normal, vec3_dec(src->p[0], plane->point));
	d[1] = vec3_dot_product(plane->normal, vec3_dec(src->p[1], plane->point));
	d[2] = vec3_dot_product(plane->normal, vec3_dec(src->p[2], plane->point));
	check_if_inside_triangle(d[0], &loc, src, 0);
	check_if_inside_triangle(d[1], &loc, src, 1);
	check_if_inside_triangle(d[2], &loc, src, 2);
	triangle1->idx = src->idx;
	triangle2->idx = src->idx;
	if (loc.inside == 0)
		return (0);
	if (loc.inside == 3)
	{
		*triangle1 = *src;
		return (1);
	}
	if (loc.inside == 1 && loc.outside == 2)
		return (form_a_triangle(&loc, plane, triangle1));
	if (loc.inside == 2 && loc.outside == 1)
		return (form_a_quadrant(&loc, plane, triangle1, triangle2));
	return (0);
}
