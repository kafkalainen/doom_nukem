/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:15:12 by tmaarela          #+#    #+#             */
/*   Updated: 2021/04/26 14:46:09 by jnivala          ###   ########.fr       */
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

t_xy	vec2_norm(t_xy v)
{
	float	mag;

	mag = sqrtf((v.x * v.x) + (v.y * v.y));
	return ((t_xy)
		{
			v.x / mag,
			v.y / mag
		});
}
