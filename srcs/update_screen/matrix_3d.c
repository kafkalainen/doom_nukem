/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:09:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/25 11:56:27 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xyz	multi_vec_matrix(t_xyz *src, t_m4x4 *x)
{
	t_xyz dst;

	dst.x = src->x * x->m[0][0] + src->y * x->m[1][0]
		+ src->z * x->m[2][0] + src->w * x->m[3][0];
	dst.y = src->x * x->m[0][1] + src->y * x->m[1][1]
		+ src->z * x->m[2][1] + src->w * x->m[3][1];
	dst.z = src->x * x->m[0][2] + src->y * x->m[1][2]
		+ src->z * x->m[2][2] + src->w * x->m[3][2];
	dst.w = src->x * x->m[0][3] + src->y * x->m[1][3]
		+ src->z * x->m[2][3] + src->w * x->m[3][3];
	return (dst);
}

t_m4x4	multiply_matrix(t_m4x4 *matrix1, t_m4x4 *matrix2)
{
	t_m4x4			m1;
	t_m4x4			m2;
	t_m4x4			mult_matrix;
	unsigned char	c;
	unsigned char	r;

	c = 0;
	m1 = *matrix1;
	m2 = *matrix2;
	while (c < 4)
	{
		r = 0;
		while (r < 4)
		{
			mult_matrix.m[r][c] = m1.m[r][0] * m2.m[0][c]
			+ m1.m[r][1] * m2.m[1][c]
			+ m1.m[r][2] * m2.m[2][c]
			+ m1.m[r][3] * m2.m[3][c];
			r++;
		}
		c++;
	}
	return (mult_matrix);
}
