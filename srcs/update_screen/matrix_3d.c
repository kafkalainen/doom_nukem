/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:09:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/23 12:15:39 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xyz	multi_vec_matrix(t_xyz *src, t_m4x4 *x)
{
	t_xyz		dst;
	float		w;

	dst.x = src->x * x->m[0][0] + src->y * x->m[1][0]
	+ src->z * x->m[2][0] + x->m[3][0];
	dst.y = src->x * x->m[0][1] + src->y * x->m[1][1]
	+ src->z * x->m[2][1] + x->m[3][1];
	dst.z = src->x * x->m[0][2] + src->y * x->m[1][2]
	+ src->z * x->m[2][2] + x->m[3][2];
	w = src->x * x->m[0][3] + src->y * x->m[1][3]
	+ src->z * x->m[2][3] + x->m[3][3];
	if (w != 0.0 && w != 1.0)
	{
		dst.x = dst.x / w;
		dst.y = dst.y / w;
		dst.z = dst.z / w;
	}
	return (dst);
}
