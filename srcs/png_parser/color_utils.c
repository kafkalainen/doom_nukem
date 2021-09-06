/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:35:32 by rzukale           #+#    #+#             */
/*   Updated: 2021/08/26 11:28:10 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	get_color_luma(int color_depth)
{
	if (color_depth == 1)
		return (LUM_ALPHA_1);
	else if (color_depth == 2)
		return (LUM_ALPHA_2);
	else if (color_depth == 4)
		return (LUM_ALPHA_4);
	else if (color_depth == 8)
		return (LUM_ALPHA_8);
	else
		return (-1);
}

int	get_color_lum(int depth)
{
	if (depth == 1)
		return (LUM_1);
	else if (depth == 2)
		return (LUM_2);
	else if (depth == 4)
		return (LUM_4);
	else if (depth == 8)
		return (LUM_8);
	else
		return (-1);
}

int	get_color_rgb(int depth)
{
	if (depth == 8)
		return (RGB_8);
	else if (depth == 16)
		return (RGB_16);
	else
		return (-1);
}

int	get_color_rgba(int depth)
{
	if (depth == 8)
		return (RGBA_8);
	else if (depth == 16)
		return (RGBA_16);
	else
		return (-1);
}

Uint32	get_transparency(Uint32 argb)
{
	return (argb & (0xFF << 24));
}
