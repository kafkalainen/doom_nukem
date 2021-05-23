/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:38:38 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/23 14:59:51 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**	Z_FAR / (Z_FAR - Z_NEAR) = 1.00010001f
**	(-Z_FAR * Z_NEAR) / (Z_FAR - Z_NEAR) = -100 / 999.9 = -0.100010001f
*/
t_triangle	create_projection(t_triangle *src)
{
	t_triangle		dst;
	static t_m4x4	matrix = (t_m4x4){{
		{0.75f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.00010001f, 1.0f},
		{0.0f, 0.0f, -0.100010001f, 0.0f}
	}};
	dst.p[0] = multi_vec_matrix(&src->p[0], &matrix);
	dst.p[1] = multi_vec_matrix(&src->p[1], &matrix);
	dst.p[2] = multi_vec_matrix(&src->p[2], &matrix);
	return (dst);
}

t_triangle	scale_triangle(t_triangle *src, t_xyz scale)
{
	t_triangle		dst;
	t_m4x4			matrix;

	matrix = scaling_matrix(scale);
	dst.p[0] = multi_vec_matrix(&src->p[0], &matrix);
	dst.p[1] = multi_vec_matrix(&src->p[1], &matrix);
	dst.p[2] = multi_vec_matrix(&src->p[2], &matrix);
	return (dst);
}

t_triangle	translate_triangle(t_triangle *src, t_xyz translation)
{
	t_triangle		dst;
	t_m4x4			matrix;

	matrix = translate_matrix(translation);
	dst.p[0] = multi_vec_matrix(&src->p[0], &matrix);
	dst.p[1] = multi_vec_matrix(&src->p[1], &matrix);
	dst.p[2] = multi_vec_matrix(&src->p[2], &matrix);
	return (dst);
}

t_triangle	rotate_triangle(t_triangle *src, float angle, char dir)
{
	t_triangle		dst;
	t_m4x4			matrix;

	if (dir == 'x')
		matrix = rotation_matrix_x(angle);
	else if (dir == 'y')
		matrix = rotation_matrix_y(angle);
	else if (dir == 'z')
		matrix = rotation_matrix_z(angle);
	else
		return (*src);
	dst.p[0] = multi_vec_matrix(&src->p[0], &matrix);
	dst.p[1] = multi_vec_matrix(&src->p[1], &matrix);
	dst.p[2] = multi_vec_matrix(&src->p[2], &matrix);
	return (dst);
}
