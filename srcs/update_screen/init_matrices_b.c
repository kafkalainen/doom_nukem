/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrices_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 09:07:16 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 14:38:51 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_m4x4	identity_matrix(void)
{
	return ((t_m4x4){{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		}});
}

/*
**	Precalculated values, when Z_FAR and Z_NEAR are fixed at 0.1f and 1000.f
**	Z_FAR / (Z_FAR - Z_NEAR) = 1.00010001f
**	(-Z_FAR * Z_NEAR) / (Z_FAR - Z_NEAR) = -100 / 999.9 = -0.100010001f
*/
t_m4x4	projection_matrix(void)
{
	return ((t_m4x4){{
			{0.75f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.00010001f, 1.0f},
			{0.0f, 0.0f, -0.0100010001f, 0.0f}
		}});
}

/*
**	Only works with translations and transformations!
*/
t_m4x4	point_at_matrix(t_xyz up, t_xyz forward, t_xyz right, t_xyz location)
{
	return ((t_m4x4){{
			{right.x, right.y, right.z, 0.0f},
			{up.x, up.y, up.z, 0.0f},
			{forward.x, forward.y, forward.z, 0.0f},
			{location.x, location.y, location.z, 1.0f}
		}});
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

void	initialize_locations(t_point_location *loc)
{
	loc->points_inside[0] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	loc->points_inside[1] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	loc->points_inside[2] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	loc->texels_inside[0] = (t_uvz){0.0f, 0.0f, 0.0f};
	loc->texels_inside[1] = (t_uvz){0.0f, 0.0f, 0.0f};
	loc->texels_inside[2] = (t_uvz){0.0f, 0.0f, 0.0f};
	loc->lumels_inside[0] = 0.0f;
	loc->lumels_inside[1] = 0.0f;
	loc->lumels_inside[2] = 0.0f;
	loc->points_outside[0] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	loc->points_outside[1] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	loc->points_outside[2] = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	loc->texels_outside[0] = (t_uvz){0.0f, 0.0f, 0.0f};
	loc->texels_outside[1] = (t_uvz){0.0f, 0.0f, 0.0f};
	loc->texels_outside[2] = (t_uvz){0.0f, 0.0f, 0.0f};
	loc->lumels_outside[0] = 0.0f;
	loc->lumels_outside[1] = 0.0f;
	loc->lumels_outside[2] = 0.0f;
	loc->inside = 0;
	loc->outside = 0;
}
