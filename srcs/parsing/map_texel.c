/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 07:54:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/10 11:37:40 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	initialize_top_texels(t_triangle *top)
{
	top->uv[0] = (t_uvz){0.0f, 1.0f, 1.0f};
	top->uv[1] = (t_uvz){0.0f, 0.0f, 1.0f};
	top->uv[2] = (t_uvz){1.0f, 0.0f, 1.0f};
}

void	initialize_bottom_texels(t_triangle *bottom)
{
	bottom->uv[0] = (t_uvz){0.0f, 1.0f, 1.0f};
	bottom->uv[1] = (t_uvz){1.0f, 0.0f, 1.0f};
	bottom->uv[2] = (t_uvz){1.0f, 1.0f, 1.0f};
}

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

int	map_texel(t_surface *surface, t_sector *sector)
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
