/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:16:10 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/08 08:44:01 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xy	vec2_mul(t_xy v, float scalar)
{
	return ((t_xy){
		v.x * scalar,
		v.y * scalar,
		1.0f
	});
}

float	vec2_dot(t_xy a, t_xy b)
{
	return (a.x * b.x + a.y * b.y);
}

float	vec2_mag(t_xy a)
{
	return (sqrtf(a.x * a.x + a.y * a.y));
}

float	vec2_ang(t_xy a, t_xy b)
{
	float	sign;
	float	angle;

	sign = -a.y * b.x + a.x * b.y;
	if (sign < 0)
		sign = -1.0f;
	else if (sign > 0)
		sign = 1.0f;
	else
		return (0.0f);
	angle = vec2_dot(a, b) / (vec2_mag(a) * vec2_mag(b));
	if (angle < -1.0)
		angle = -1.0f;
	else if (angle > 1.0)
		angle = 1.0f;
	return (sign * acosf(angle));
}

t_xy	vec2_normal(t_xy p0, t_xy p1)
{
	return ((t_xy){(p1.y - p0.y), -(p1.x - p0.x), 1.0f});
}
