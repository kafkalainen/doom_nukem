/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:15:12 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/01 08:59:32 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xy	vec2(float x, float y)
{
	return ((t_xy){x, y});
}

t_xy	vec2_add(t_xy a, t_xy b)
{
	return ((t_xy)
		{
			a.x + b.x,
			a.y + b.y
		});
}

t_xy	vec2_dec(t_xy a, t_xy b)
{
	return ((t_xy)
		{
			a.x - b.x,
			a.y - b.y
		});
}

t_xy	vec2_rot(t_xy v, float angle)
{
	return ((t_xy)
		{
			v.x * cosf(angle) - v.y * sinf(angle),
			v.x * sinf(angle) + v.y * cosf(angle)
		});
}

t_xy	vec2_unit_vector(t_xy v)
{
	float	mag;

	mag = sqrtf((v.x * v.x) + (v.y * v.y));
	mag = 1 / mag;
	return ((t_xy)
		{
			v.x * mag,
			v.y * mag
		});
}
