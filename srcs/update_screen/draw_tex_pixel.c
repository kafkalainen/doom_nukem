/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:22:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/26 11:02:33 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	get_texel(t_uv *coord, t_uv *limits, Uint32 *pixels)
{
	if (coord->u < 0)
		coord->u = 0;
	if (coord->v < 0)
		coord->v = 0;
	if (coord->u > limits->u - 1)
		coord->u = limits->u - 1;
	if (coord->v > limits->v - 1)
		coord->v = limits->v - 1;
	return ((Uint32)pixels[(coord->v * limits->u) + coord->u]);
}
