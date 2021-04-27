/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_scale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:03:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/27 13:13:50 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	colour_scale(Uint32 hex, float scale)
{
	t_argb	argb;

	if (scale > 1)
		scale = 1;
	if (scale < 0)
		scale = 0;
	argb.alpha = (hex >> 24);
	argb.red = (hex >> 16);
	argb.green = (hex >> 8);
	argb.blue = (hex);
	argb.red *= scale;
	argb.green *= scale;
	argb.blue *= scale;
	return ((argb.alpha << 24) | (argb.red << 16)
		| (argb.green << 8) | (argb.blue));
}
