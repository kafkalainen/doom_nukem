/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:36:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 10:34:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**	Get distance to intersection gets the scalar of the vector dir. If there
**	is no scalar, function will return false.
*/
t_bool	vec2_get_scalar_to_intersection(t_xy pos, t_xy dir, t_wall *wall,
		float *t)
{
	t_xy	vectors[3];
	float	dot;
	float	t1;
	float	t2;

	vectors[0] = vec2_dec(pos, vec2(wall->top.p[1].x, wall->top.p[1].z));
	vectors[1] = vec2_dec(vec2(wall->top.p[2].x, wall->top.p[2].z),
			vec2(wall->top.p[1].x, wall->top.p[1].z));
	vectors[2] = vec2(-dir.y, dir.x);
	dot = vec2_dot(vectors[1], vectors[2]);
	if (fabsf(dot) < 0.000001)
		return (false);
	dot = 1 / dot;
	t1 = vec2_cross(vectors[1], vectors[0]) * dot;
	t2 = vec2_dot(vectors[0], vectors[2]) * dot;
	if (t1 >= 0.0f && (t2 >= 0.0f && t2 <= 1.0f))
	{
		*t = t1;
		return (true);
	}
	return (false);
}
