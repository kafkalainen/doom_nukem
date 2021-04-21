/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_scale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:03:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/21 20:26:37 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	colour_scale(Uint32 hex, float scale)
{
	t_argb	argb;

	argb.a = (hex & 0xFF000000);
	argb.r = (hex & 0x00FF0000) * scale;
	argb.g = (hex & 0x0000FF00) * scale;
	argb.b = (hex & 0x000000FF) * scale;
	return ((argb.a | (argb.r & 0x00FF0000)
			| (argb.g & 0x0000FF00) | (argb.b & 0x000000FF)));
}
