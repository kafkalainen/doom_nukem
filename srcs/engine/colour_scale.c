/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_scale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:03:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/30 13:28:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	colour_scale(Uint32 hex, float lumel, float lightness)
{
	t_argb	argb;

	if (lumel > 1)
		lumel = 1;
	if (lumel < 0)
		lumel = 0;
	if (lightness > 1)
		lightness = 1;
	if (lightness < 0)
		lightness = 0;
	argb.alpha = (hex >> 24);
	argb.red = (hex >> 16);
	argb.green = (hex >> 8);
	argb.blue = (hex);
	argb.red *= lumel * lightness;
	argb.green *= lumel * lightness;
	argb.blue *= lumel * lightness;
	return ((argb.alpha << 24) | (argb.red << 16)
		| (argb.green << 8) | (argb.blue));
}
