/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:36:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/06 15:08:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	interpolate_y(t_height *height, t_xy cutpoint, t_point *p0, t_point *p1)
{
	float	full_mag;
	float	cut_mag;

	full_mag = vec2_mag(vec2_dec(p1->x0, p0->x0));
	cut_mag = vec2_mag(vec2_dec(p1->x0, cutpoint));
	height->ground = p1->height.ground - (p1->height.ground - p0->height.ground)
		* (cut_mag / full_mag);
	height->ceiling = p1->height.ceiling - (p1->height.ceiling - p0->height.ceiling)
		* (cut_mag / full_mag);
}
