/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:09:41 by ngontjar          #+#    #+#             */
/*   Updated: 2020/10/14 16:16:02 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_xy			vec2_rot(t_xy v, double angle)
{
	return ((t_xy){
		v.x * cos(angle) - v.y * sin(angle),
		v.x * sin(angle) + v.y * cos(angle)
	});
}

t_xy			vec2_norm(t_xy v)
{
	double mag;

	mag = sqrt((v.x * v.x) + (v.y * v.y));
	return ((t_xy){
		v.x / mag,
		v.y / mag
	});
}

t_xy			vec2_mul(t_xy v, double scalar)
{
	return ((t_xy){
		v.x * scalar,
		v.y * scalar
	});
}

double			vec2_dot(t_xy a, t_xy b)
{
	return (a.x * b.x + a.y * b.y);
}

double			ft_map(double in, t_range from, t_range to)
{
	return (to.x + ((in - from.x) * (to.y - to.x)) / (from.y - from.x));
}
