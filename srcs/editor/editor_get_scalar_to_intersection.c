/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_get_scalar_to_intersection.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 10:26:51 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/11 10:53:20 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	editor_get_scalar_to_intersection(t_screen_xy pos, t_screen_xy dir,
		t_editor_walls *wall, float *t)
{
	t_xy	vectors[3];
	float	dot;
	float	t1;
	float	t2;

	vectors[0] = vec2_dec(vec2(pos.x, pos.y), vec2(wall->x0.x, wall->x0.y));
	vectors[1] = vec2_dec(vec2(wall->next->x0.x, wall->next->x0.y),
			vec2(wall->x0.x, wall->x0.y));
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
