/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strafe_vector_along_the_wall.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 09:54:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/19 10:14:42 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xyz	strafe_vector_along_the_wall(t_xyz dir, t_wall *wall)
{
	float	angle;
	t_xyz	wall_vector;

	wall_vector = vec3_unit_vector(vec3_dec(wall->bottom.p[0],
		wall->bottom.p[2]));
	angle = vec3_angle(dir, wall_vector);
	if (angle < 1.57f && angle >= 0.0f)
		return (wall_vector);
	else
		return (vec3_mul(wall_vector, -1.0));
}
