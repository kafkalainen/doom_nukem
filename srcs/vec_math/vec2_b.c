/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:16:10 by tmaarela          #+#    #+#             */
/*   Updated: 2021/02/19 14:38:26 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

t_xy			vec2_rot(t_xy v, float angle)
{
	return ((t_xy){
		v.x * cosf(angle) - v.y * sinf(angle),
		v.x * sinf(angle) + v.y * cosf(angle)
	});
}

t_xy			vec2_norm(t_xy v)
{
	float mag;

	mag = sqrtf((v.x * v.x) + (v.y * v.y));
	return ((t_xy){
		v.x / mag,
		v.y / mag
	});
}

t_xy			vec2_mul(t_xy v, float scalar)
{
	return ((t_xy){
		v.x * scalar,
		v.y * scalar
	});
}

float			vec2_dot(t_xy a, t_xy b)
{
	return (a.x * b.x + a.y * b.y);
}

float			vec2_mag(t_xy a)
{
	return sqrtf(a.x * a.x + a.y * a.y);
}

float			vec2_ang(t_xy a, t_xy b)
{
	return acosf(vec2_dot(a, b) / (vec2_mag(a) * vec2_mag(b)));
}

float			ft_map(float in, t_range from, t_range to)
{
	return (to.x + ((in - from.x) * (to.y - to.x)) / (from.y - from.x));
}
