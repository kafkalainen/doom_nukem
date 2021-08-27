/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_matrices_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 10:59:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/27 12:40:10 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_triangle	apply_world_matrix(float angle_x, float angle_z,
	t_xyz translation, t_triangle *src)
{
	t_triangle	dst;
	t_m4x4		world;
	t_m4x4		matrix_x;
	t_m4x4		matrix_z;
	t_m4x4		matrix_trans;

	dst = *src;
	matrix_x = rotation_matrix_x(angle_x);
	matrix_z = rotation_matrix_z(angle_z);
	matrix_trans = translate_matrix(translation);
	world = identity_matrix();
	world = multiply_matrix(&matrix_z, &matrix_x);
	world = multiply_matrix(&world, &matrix_trans);
	dst.p[0] = multi_vec_matrix(&src->p[0], &world);
	dst.p[1] = multi_vec_matrix(&src->p[1], &world);
	dst.p[2] = multi_vec_matrix(&src->p[2], &world);
	return (dst);
}

void	create_target_vector(t_player *plr)
{
	t_m4x4	z_matrix;
	t_m4x4	y_matrix;
	t_m4x4	x_matrix;
	t_m4x4	combined;

	plr->up = (t_xyz){0.0f,1.0f,0.0f,1.0f};
	plr->target = (t_xyz){0.0f, 0.0f, 1.0f, 0.0f};
	z_matrix = rotation_matrix_z(plr->roll);
	y_matrix = rotation_matrix_y(plr->yaw);
	x_matrix = rotation_matrix_x(plr->pitch);
	combined = multiply_matrix(&y_matrix, &x_matrix);
	combined = multiply_matrix(&combined, &z_matrix);
	plr->look_dir = multi_vec_matrix(&plr->target, &combined);
	plr->target = vec3_add(plr->pos, plr->look_dir);
}

t_xyz	translate_point(t_xyz *src, t_xyz translation)
{
	t_xyz			dst;
	t_m4x4			matrix;

	matrix = translate_matrix(translation);
	dst = multi_vec_matrix(src, &matrix);
	return (dst);
}
