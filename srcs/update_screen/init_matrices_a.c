/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrices_a.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:18:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/22 11:08:48 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_m4x4	translate_matrix(t_xyz t)
{
	return ((t_m4x4){{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{t.x, t.y, t.z, 1.0f}}});
}

t_m4x4	scaling_matrix(t_xyz a)
{
	return ((t_m4x4){{
			{a.x, 0.0f, 0.0f, 0.0f},
			{0.0f, a.y, 0.0f, 0.0f},
			{0.0f, 0.0f, a.z, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}}});
}

t_m4x4	rotation_matrix_x(float angle)
{
	return ((t_m4x4){{
			{1.0, 0.0f, 0.0f, 0.0f},
			{0.0f, cosf(angle), sinf(angle), 0.0f},
			{0.0f, -sinf(angle), cosf(angle), 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}}});
}

t_m4x4	rotation_matrix_y(float angle)
{
	return ((t_m4x4){{
			{cosf(angle), 0.0f, sinf(angle), 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{-sinf(angle), 0.0f, cosf(angle), 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}}});
}

t_m4x4	rotation_matrix_z(float angle)
{
	return ((t_m4x4){{
			{cosf(angle), sinf(angle), 0.0f, 0.0f},
			{-sinf(angle), cosf(angle), 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}}});
}
