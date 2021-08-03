/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_g.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 11:39:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/03 14:53:28 by jnivala          ###   ########.fr       */
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

Uint32	vec3_check_same_sidedness(t_xyz p1, t_xyz p2, t_xyz a, t_xyz b)
{
		t_xyz	cross_products[2];

		cross_products[0] = vec3_unit_vector(vec3_cross_product(vec3_dec(b, a), vec3_dec(p1, a)));
		cross_products[1] = vec3_unit_vector(vec3_cross_product(vec3_dec(b, a), vec3_dec(p2, a)));
		if (vec3_dot_product(cross_products[0], cross_products[1]) >= 0.0f)
			return (1);
		else
			return (0);
}

Uint32	vec3_is_inside_triangle(t_triangle *tri, t_xyz point)
{
	t_xyz	test_vector;

	if (vec3_check_same_sidedness(point, tri->p[0], tri->p[1], tri->p[2])
		&& vec3_check_same_sidedness(point, tri->p[1], tri->p[0], tri->p[2])
		&& vec3_check_same_sidedness(point, tri->p[2], tri->p[0], tri->p[1]))
		{
			test_vector = vec3_unit_vector(vec3_cross_product(
				vec3_dec(tri->p[0], tri->p[1]), vec3_dec(tri->p[0], tri->p[2])));
			if (ft_fabsf(vec3_dot_product(vec3_dec(tri->p[0], point), test_vector)) <= 0.01f)
			return (1);
		}
	return (0);
}
