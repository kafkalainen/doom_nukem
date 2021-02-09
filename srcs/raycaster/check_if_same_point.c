/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_same_point.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:40:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/09 15:02:10 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"


static float	get_distance(t_xy p1, t_xy p2)
{
	return (sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));
}

int				check_if_same_point(float current_angle, t_ray_fov *fov)
{

	if (current_angle == 0.0f
		&& get_distance(fov->left_point, fov->right_point) < 0.001)
		return (TRUE);
	else
		return (FALSE);
}
