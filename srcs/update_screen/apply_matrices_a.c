/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_matrices_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:38:38 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/25 13:53:31 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_triangle	create_projection(t_triangle *src)
{
	t_triangle			dst;
	t_m4x4				matrix;

	dst = *src;
	matrix = projection_matrix();
	dst.p[0] = multi_vec_matrix(&src->p[0], &matrix);
	dst.p[1] = multi_vec_matrix(&src->p[1], &matrix);
	dst.p[2] = multi_vec_matrix(&src->p[2], &matrix);
	return (dst);
}

t_triangle	scale_triangle(t_triangle *src, t_xyz scale)
{
	t_triangle		dst;
	t_m4x4			matrix;

	dst = *src;
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

	dst = *src;
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

	dst = *src;
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

t_triangle	apply_camera(t_xyz pos, t_xyz target, t_xyz up, t_triangle *src)
{
	t_xyz	next_forward;
	t_xyz	next_up;
	t_xyz	next_right;
	t_m4x4	view_matrix;
	t_triangle	dst;

	next_forward = vec3_dec(target, pos);
	next_forward = vec3_unit_vector(next_forward);
	next_up = vec3_mul(next_forward, vec3_dot_product(up, next_forward));
	next_up = vec3_dec(up, next_up);
	next_up = vec3_unit_vector(next_up);
	next_right = vec3_cross_product(next_up, next_forward);
	view_matrix = point_at_matrix(next_up, next_forward, next_right, pos);
	view_matrix = inverse_matrix(&view_matrix);
	dst.p[0] = multi_vec_matrix(&src->p[0], &view_matrix);
	dst.p[1] = multi_vec_matrix(&src->p[1], &view_matrix);
	dst.p[2] = multi_vec_matrix(&src->p[2], &view_matrix);
	return (dst);
}
