/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:14:05 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/28 19:26:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

t_xy	vec2_perpendicular(t_xy x0, t_xy x1)
{
	t_xy	vector;

	vector = vec2_dec(x1, x0);
	return (vec2(-vector.y, vector.x));
}
