/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_to_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 11:58:40 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/26 14:33:11 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	calculate_distance_to_plane(t_xyz point, t_xyz plane_normal,
	 t_xyz plane_point, float *d)
{
	t_xyz	tri_point;

	tri_point = vec3_unit_vector(point);
	*d = plane_normal.x * tri_point.x
		+ plane_normal.y * tri_point.y
		+ plane_normal.z * tri_point.z
		- vec3_dot_product(plane_normal, plane_point);
}

static void	check_if_inside_triangle(float *d, t_point_location *loc,
	t_xyz point, t_uvz uv)
{
	if (*d >= 0)
	{
		loc->texels_inside[loc->inside] = uv;
		loc->points_inside[loc->inside++] = point;
	}
	else
	{
		loc->texels_outside[loc->outside] = uv;
		loc->points_outside[loc->outside++] = point;
	}
}

static void	initialize_locations(t_point_location *loc)
{
	loc->points_inside[0] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	loc->points_inside[1] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	loc->points_inside[2] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	loc->points_outside[0] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	loc->points_outside[1] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	loc->points_outside[2] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	loc->inside = 0;
	loc->outside = 0;
}

int		clip_against_plane(t_xyz plane_point, t_xyz plane_normal,
		t_triangle *src, t_triangle *triangle1, t_triangle *triangle2)
{
	t_point_location	loc;
	float				d[3];

	initialize_locations(&loc);
	plane_normal = vec3_unit_vector(plane_normal);
	calculate_distance_to_plane(src->p[0], plane_normal, plane_point, &d[0]);
	calculate_distance_to_plane(src->p[1], plane_normal, plane_point, &d[1]);
	calculate_distance_to_plane(src->p[2], plane_normal, plane_point, &d[2]);
	check_if_inside_triangle(&d[0], &loc, src->p[0], src->uv[0]);
	check_if_inside_triangle(&d[1], &loc, src->p[1], src->uv[1]);
	check_if_inside_triangle(&d[2], &loc, src->p[2], src->uv[2]);
	if (loc.inside == 0)
		return (0);
	if (loc.inside == 3)
	{
		*triangle1 = *src;
		return (1);
	}
	if (loc.inside == 1 && loc.outside == 2)
	{
		triangle1->p[0] = loc.points_inside[0];
		triangle1->uv[0] = loc.texels_inside[0];
		triangle1->p[1] = vec3_intersection_with_plane(plane_point, plane_normal, loc.points_inside[0], loc.points_outside[0], &loc.texel_offset);
		triangle1->uv[1].u = loc.texel_offset * (loc.texels_outside[0].u - loc.texels_inside[0].u) + loc.texels_inside[0].u;
		triangle1->uv[1].v = loc.texel_offset * (loc.texels_outside[0].v - loc.texels_inside[0].v) + loc.texels_inside[0].v;
		triangle1->uv[1].w = loc.texel_offset * (loc.texels_outside[0].w - loc.texels_inside[0].w) + loc.texels_inside[0].w;
		triangle1->p[2] = vec3_intersection_with_plane(plane_point, plane_normal, loc.points_inside[0], loc.points_outside[1], &loc.texel_offset);
		triangle1->uv[2].u = loc.texel_offset * (loc.texels_outside[1].u - loc.texels_inside[0].u) + loc.texels_inside[0].u;
		triangle1->uv[2].v = loc.texel_offset * (loc.texels_outside[1].v - loc.texels_inside[0].v) + loc.texels_inside[0].v;
		triangle1->uv[2].w = loc.texel_offset * (loc.texels_outside[1].w - loc.texels_inside[0].w) + loc.texels_inside[0].w;
		return (1);
	}
	if (loc.inside == 2 && loc.outside == 1)
	{
		triangle1->p[0] = loc.points_inside[0];
		triangle1->uv[0] = loc.texels_inside[0];
		triangle1->p[1] = loc.points_inside[1];
		triangle1->uv[1] = loc.texels_inside[1];
		triangle1->p[2] = vec3_intersection_with_plane(plane_point, plane_normal, loc.points_inside[0], loc.points_outside[0], &loc.texel_offset);
		triangle1->uv[2].u = loc.texel_offset * (loc.texels_outside[1].u - loc.texels_inside[0].u) + loc.texels_inside[0].u;
		triangle1->uv[2].v = loc.texel_offset * (loc.texels_outside[1].v - loc.texels_inside[0].v) + loc.texels_inside[0].v;
		triangle1->uv[2].w = loc.texel_offset * (loc.texels_outside[1].w - loc.texels_inside[0].w) + loc.texels_inside[0].w;
		triangle2->p[0] = loc.points_inside[1];
		triangle2->uv[0] = loc.texels_inside[1];
		triangle2->p[0] = triangle1->p[1];
		triangle2->uv[0] = triangle1->uv[1];
		triangle2->p[2] = vec3_intersection_with_plane(plane_point, plane_normal, loc.points_inside[1], loc.points_outside[0], &loc.texel_offset);
		triangle2->uv[2].u = loc.texel_offset * (loc.texels_outside[0].u - loc.texels_inside[1].u) + loc.texels_inside[1].u;
		triangle2->uv[2].v = loc.texel_offset * (loc.texels_outside[0].v - loc.texels_inside[1].v) + loc.texels_inside[1].v;
		triangle2->uv[2].w = loc.texel_offset * (loc.texels_outside[0].w - loc.texels_inside[1].w) + loc.texels_inside[1].w;
		return (2);
	}
	return (-1);
}
