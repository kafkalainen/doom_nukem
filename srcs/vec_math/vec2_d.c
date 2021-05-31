/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:36:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/31 11:24:51 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**	ERRORZ!!
*/
// void	interpolate_y(t_height *height, t_xy cutpoint, t_point *p0, t_point *p1)
// {
// 	float	full_mag;
// 	float	cut_mag;

// 	full_mag = vec2_mag(vec2_dec(p1->x0, p0->x0));
// 	cut_mag = vec2_mag(vec2_dec(p1->x0, cutpoint));
// 	height->ground = p1->height.ground - (p1->height.ground - p0->height.ground)
// 		* (cut_mag / full_mag);
// 	height->ceiling = p1->height.ceiling - (p1->height.ceiling
// 			- p0->height.ceiling) * (cut_mag / full_mag);
// }

// void	interpolate_uv(t_xy *ground_uv, t_xy cutpoint, t_point *p0, t_point *p1)
// {
// 	float	full_mag;
// 	float	cut_mag;

// 	full_mag = vec2_mag(vec2_dec(p1->x0, p0->x0));
// 	cut_mag = vec2_mag(vec2_dec(p1->x0, cutpoint));
// 	ground_uv->x = p1->ground_uv.x - (p1->ground_uv.x - p0->ground_uv.x)
// 		* (cut_mag / full_mag);
// 	ground_uv->y = p1->ground_uv.y - (p1->ground_uv.y - p0->ground_uv.y)
// 		* (cut_mag / full_mag);
// }

// float	vec2_distance_from_point_to_line(t_xy *p0, t_xy *p1, t_xy *x0)
// {
// 	float	dist;

// 	dist = fabsf((p1->x - p0->x) * (p0->y - x0->y)
// 			- (p0->x - x0->x) * (p1->y - p0->y))
// 		/ vec2_eucl_dist(*p0, *p1);
// 	return (dist);
// }
