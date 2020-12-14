/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:15:00 by ngontjar          #+#    #+#             */
/*   Updated: 2020/10/14 16:16:23 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_xy			vec2(double x, double y)
{
	return ((t_xy){x, y});
}

t_xy			vec2_add(t_xy a, t_xy b)
{
	return ((t_xy)
	{
		a.x + b.x,
		a.y + b.y
	});
}

t_xy			vec2_dec(t_xy a, t_xy b)
{
	return ((t_xy)
	{
		a.x - b.x,
		a.y - b.y
	});
}
