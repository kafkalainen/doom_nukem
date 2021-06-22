/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 07:54:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/22 09:03:30 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_uvz	interpolate_coordinate(t_xyz coordinate, t_plgn *bounding_box)
{
	t_uvz	texel;

	texel.u = interpolate_points(
			bounding_box->bottom_left.x, coordinate.x,
			bounding_box->bottom_left.x,
			bounding_box->bottom_right.x);
	texel.v = interpolate_points(
			bounding_box->top_left.y, coordinate.z,
			bounding_box->top_left.y,
			bounding_box->bottom_right.y);
	texel.w = 1.0f;
	return (texel);
}

int				map_texel(t_surface *surface, t_sector *sector)
{

	surface->tri.uv[0] = interpolate_coordinate(surface->tri.p[0],
		&sector->bounding_box);
	surface->tri.uv[1] = interpolate_coordinate(surface->tri.p[1],
		&sector->bounding_box);
	surface->tri.uv[2] = interpolate_coordinate(surface->tri.p[2],
		&sector->bounding_box);
	surface->tri.colour = white;
	return (0);
}
