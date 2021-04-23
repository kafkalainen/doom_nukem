/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_scale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:03:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/23 14:10:45 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	colour_scale(Uint32 hex, float scale)
{
	t_argb	argb;

	if (scale > 1)
		scale = 1;
	argb.a = (hex >> 24);
	argb.r = (hex >> 16);
	argb.g = (hex >> 8);
	argb.b = (hex);
	argb.r *= scale;
	argb.g *= scale;
	argb.b *= scale;
	return ( (argb.a << 24) | (argb.r << 16) | (argb.g << 8) | (argb.b));
}
