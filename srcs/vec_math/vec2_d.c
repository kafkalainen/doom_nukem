/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:36:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/07 11:22:20 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xy	vec2_div(t_xy a, float scalar)
{
	scalar = 1 / scalar;
	return ((t_xy){
		a.x * scalar,
		a.y * scalar,
		1.0f
	});
}

float	vec2_ang_simple(t_xy a, t_xy b)
{
	return (acosf(vec2_dot(a, b) / (vec2_mag(a) * vec2_mag(b))));
}

t_bool	point_inside_fov(t_xy p0, t_xy p1, t_xy p2, t_xy p)
{
	float	plane_p0p1;
	float	plane_p2p0;

	plane_p0p1 = (p0.x - p.x) * (p1.y - p.y) - (p1.x - p.x) * (p0.y - p.y);
	plane_p2p0 = (p2.x - p.x) * (p0.y - p.y) - (p0.x - p.x) * (p2.y - p.y);
	plane_p0p1 = ft_signf(plane_p0p1);
	plane_p2p0 = ft_signf(plane_p2p0);
	if (plane_p0p1 == plane_p2p0)
		return (true);
	else
		return (false);
}
