/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_colours.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:04:55 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/09 14:08:35 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	calc_colours(Uint32 *bg, Uint32 *fg, float *lightness)
{
	*bg = 0xFFFFFFFF;
	if (*lightness < 1.0f)
		*bg = colour_scale(0xFFFFFFFF, 1.0f, *lightness, 1.0f);
	*fg = 0xFFFFCC00;
	if (*lightness < 1.0f)
		*fg = colour_scale(0xFFFFCC00, 1.0f, *lightness, 1.0f);
}
