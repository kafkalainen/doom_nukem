/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrices_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 09:07:16 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/25 10:57:16 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_m4x4	identity_matrix(void)
{
	return (t_m4x4){{
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
	}};
}

/*
**	Z_FAR / (Z_FAR - Z_NEAR) = 1.00010001f
**	(-Z_FAR * Z_NEAR) / (Z_FAR - Z_NEAR) = -100 / 999.9 = -0.100010001f
*/
t_m4x4	projection_matrix(void)
{
	return (t_m4x4){{
		{0.75f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.00010001f, 1.0f},
		{0.0f, 0.0f, -0.100010001f, 0.0f}
	}};
}

/*
**	Only works with translations and transformations!
*/
t_m4x4	point_to_matrix(t_xyz up, t_xyz forward, t_xyz right, t_xyz location)
{
	return (t_m4x4){{
		{right.x, right.y, right.z, 0.0f},
		{up.x, up.y, up.z, 0.0f},
		{forward.x, forward.y, forward.z, 0.0f},
		{location.x, location.y, location.z, 1.0f}
	}};
}

t_m4x4	inverse_matrix(t_m4x4 *rot_trans_matrix)
{
		t_m4x4	new_matrix;

		new_matrix.m[0][0] = rot_trans_matrix->m[0][0];
		new_matrix.m[0][1] = rot_trans_matrix->m[1][0];
		new_matrix.m[0][2] = rot_trans_matrix->m[2][0];
		new_matrix.m[0][3] = 0.0f;
		new_matrix.m[1][0] = rot_trans_matrix->m[0][1];
		new_matrix.m[1][1] = rot_trans_matrix->m[1][1];
		new_matrix.m[1][2] = rot_trans_matrix->m[2][1];
		new_matrix.m[1][3] = 0.0f;
		new_matrix.m[2][0] = rot_trans_matrix->m[0][2];
		new_matrix.m[2][1] = rot_trans_matrix->m[1][2];
		new_matrix.m[2][2] = rot_trans_matrix->m[2][2];
		new_matrix.m[2][3] = 0.0f;
		new_matrix.m[2][3] = rot_trans_matrix->m[3][2];
		new_matrix.m[3][0] = -(rot_trans_matrix->m[3][0] * new_matrix.m[0][0]
			+ rot_trans_matrix->m[3][1] * new_matrix.m[1][0]
			+ rot_trans_matrix->m[3][2] * new_matrix.m[2][0]);
		new_matrix.m[3][1] = -(rot_trans_matrix->m[3][0] * new_matrix.m[0][1]
			+ rot_trans_matrix->m[3][1] * new_matrix.m[1][1]
			+ rot_trans_matrix->m[3][2] * new_matrix.m[2][1]);
		new_matrix.m[3][2] = -(rot_trans_matrix->m[3][0] * new_matrix.m[0][2]
			+ rot_trans_matrix->m[3][1] * new_matrix.m[1][2]
			+ rot_trans_matrix->m[3][2] * new_matrix.m[2][2]);
		new_matrix.m[3][3] = 1.0f;
		return (new_matrix);
}
