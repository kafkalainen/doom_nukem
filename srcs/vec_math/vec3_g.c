/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_g.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 11:39:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/09 13:23:07 by rzukale          ###   ########.fr       */
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

// t_bool	run_tests(t_home *home)
// {
// 	int		cur_sector[5];
// 	t_xyz	coord[5];
// 	t_xyz	isection[5];

// 	ft_putendl("idx: 50");
// 	cur_sector[0] = 50;
// 	coord[0] = vec3(-25.140568f, 1.500000f, 20.981659f);
// 	ft_putbool(check_if_moved_through_portal(&cur_sector[0], coord[0], home));
// 	ft_putnbr(find_current_sector(home, coord[0], 50, &isection[0]));
// 	ft_putchar('\n');
// 	cur_sector[1] = 50;
// 	coord[1] = vec3(-25.160471f, 1.500000f, 20.895657f);
// 	ft_putbool(check_if_moved_through_portal(&cur_sector[1], coord[1], home));
// 	ft_putnbr(find_current_sector(home, coord[1], 50, &isection[1]));
// 	ft_putchar('\n');
// 	cur_sector[2] = 50;
// 	coord[2] = vec3(-25.150467f, 0.600000f, 20.884480f);
// 	ft_putbool(check_if_moved_through_portal(&cur_sector[2], coord[2], home));
// 	ft_putnbr(find_current_sector(home, coord[2], 50, &isection[2]));
// 	ft_putchar('\n');
// 	cur_sector[3] = 50;
// 	coord[3] = vec3(-25.085194f, 0.600000f, 20.942373f);
// 	ft_putbool(check_if_moved_through_portal(&cur_sector[3], coord[3], home));
// 	ft_putnbr(find_current_sector(home, coord[3], 50, &isection[3]));
// 	ft_putendl("cur_sector: 34");
// 	ft_putchar('\n');
// 	cur_sector[0] = 34;
// 	coord[0] = vec3(-25.140568f, 1.500000f, 20.981659f);
// 	ft_putbool(check_if_moved_through_portal(&cur_sector[0], coord[0], home));
// 	ft_putnbr(find_current_sector(home, coord[0], 34, &isection[0]));
// 	ft_putchar('\n');
// 	cur_sector[1] = 34;
// 	coord[1] = vec3(-25.160471f, 1.500000f, 20.895657f);
// 	ft_putbool(check_if_moved_through_portal(&cur_sector[1], coord[1], home));
// 	ft_putnbr(find_current_sector(home, coord[1], 34, &isection[1]));
// 	ft_putchar('\n');
// 	cur_sector[2] = 34;
// 	coord[2] = vec3(-25.150467f, 0.600000f, 20.884480f);
// 	ft_putbool(check_if_moved_through_portal(&cur_sector[2], coord[2], home));
// 	ft_putnbr(find_current_sector(home, coord[2], 34, &isection[2]));
// 	ft_putchar('\n');
// 	cur_sector[3] = 34;
// 	coord[3] = vec3(-25.085194f, 0.600000f, 20.942373f);
// 	ft_putbool(check_if_moved_through_portal(&cur_sector[3], coord[3], home));
// 	ft_putnbr(find_current_sector(home, coord[3], 34, &isection[3]));
// 	ft_putchar('\n');
// 	return (true);
// }

// t_bool	vec3_ray_intersects_triangle(t_triangle *inTriangle,
//	t_xyz ray_origin, t_xyz ray_vector, t_xyz *isection)
// {
// 	const float	epsilon = 0.0000001f;
// 	t_xyz		p[3];
// 	t_xyz		edge[2];
// 	t_xyz		h;
// 	t_xyz		s;
// 	t_xyz		q;
// 	float		a;
// 	float		f;
// 	float		u;
// 	float		v;
// 	float		t;

// 	p[0] = inTriangle->p[0];
// 	p[1] = inTriangle->p[1];
// 	p[2] = inTriangle->p[2];
// 	edge[0] = vec3_dec(p[1], p[0]);
// 	edge[1] = vec3_dec(p[2], p[0]);
// 	h = vec3_cross_product(edge[1], ray_vector);
// 	a = vec3_dot_product(edge[0], h);
// 	if (a > -epsilon && a < epsilon)
// 		return (false);
// 	f = 1.0f / a;
// 	s = vec3_dec(ray_origin, p[0]);
// 	u = f * vec3_dot_product(h, s);
// 	if (u < 0.0f || u > 1.0f)
// 		return (false);
// 	q = vec3_cross_product(edge[0], s);
// 	v = f * vec3_dot_product(q, ray_vector);
// 	if (v < 0.0f || u + v > 1.0f)
// 		return (false);
// 	t = f * vec3_dot_product(q, edge[1]);
// 	if (t > epsilon)
// 	{
// 		*isection = vec3_add(ray_origin, vec3_mul(ray_vector, t));
// 		return (true);
// 	}
// 	else
// 		return (false);
// }
