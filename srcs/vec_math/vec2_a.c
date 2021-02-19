/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:15:12 by tmaarela          #+#    #+#             */
/*   Updated: 2021/02/19 14:37:26 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

t_xy			vec2(float x, float y)
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
