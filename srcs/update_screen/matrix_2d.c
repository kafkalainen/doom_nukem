/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:10:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/08 08:24:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xy	multiply_vec2_with_2d_matrix(t_xy *src, t_m3x3 *x)
{
	t_xy dst;

	dst.x = src->x * x->m[0][0]
		+ src->y * x->m[1][0]
		+ src->w * x->m[2][0];
	dst.y = src->x * x->m[0][1]
		+ src->y * x->m[1][1]
		+ src->w * x->m[2][1];
	dst.w = src->x * x->m[0][2]
		+ src->y * x->m[1][2]
		+ src->w * x->m[2][2];
	return (dst);
}

t_m3x3	multiply_2d_matrix_with_2d_matrix(t_m3x3 *m1, t_m3x3 *m2)
{
	t_m3x3			mult_matrix;
	int				c;
	int				r;

	c = 0;
	while (c < 3)
	{
		r = 0;
		while (r < 3)
		{
			mult_matrix.m[r][c] = m1->m[r][0] * m2->m[0][c]
				+ m1->m[r][1] * m2->m[1][c]
				+ m1->m[r][2] * m2->m[2][c];
			r++;
		}
		c++;
	}
	return (mult_matrix);
}

t_m3x3		scaling_matrix_2d(t_xy scale)
{
	t_m3x3	m;

	m = (t_m3x3){{{scale.x, 0.0f, 0.0f},
				{0.0f, scale.y, 0.0f},
				{0.0f, 0.0f, 1.0f}}};
	return (m);
}

t_m3x3		translation_matrix_2d(t_xy translation)
{
	t_m3x3	m;

	m = (t_m3x3){{{1.0f, 0.0f, 0.0f},
				{0.0f, 1.0f, 0.0f},
				{translation.x, translation.y, 1.0f}}};
	return (m);
}

t_m3x3		rotation_matrix_2d(float angle)
{
	t_m3x3	m;

	m = (t_m3x3){{{cosf(angle), -sinf(angle), 0.0f},
				{sinf(angle), cosf(angle), 0.0f},
				{0.0f, 0.0f, 1.0f}}};
	return (m);
}
