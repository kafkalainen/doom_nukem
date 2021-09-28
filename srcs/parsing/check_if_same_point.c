/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_same_point.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 17:50:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/28 10:02:42 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	vec3_check_if_same_point(t_xyz a, t_xyz b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w)
		return (true);
	else
		return (false);
}

t_bool	vec2_check_if_same_point(t_xy a, t_xy b)
{
	if (a.x == b.x && a.y == b.y)
		return (true);
	else
		return (false);
}
