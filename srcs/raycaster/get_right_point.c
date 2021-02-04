/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_right_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:48:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/04 12:09:18 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

t_xy	get_right_point(t_point *p0, t_point *start, t_player *plr)
{
	t_ray			ray;
	t_intersection	sect;
	t_xy			cutpoint;

	ray.pos = vec2(0, 0);
	ray.dir = vec2_rot(plr->dir, DEG_TO_RAD * FOV * 0.5);
	calc_intersection(p0, start, &ray, &sect);
	cutpoint = line_intersection(&sect);
	return (cutpoint);
}
