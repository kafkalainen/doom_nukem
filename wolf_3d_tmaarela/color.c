/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:32:59 by ngontjar          #+#    #+#             */
/*   Updated: 2020/10/14 14:14:22 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_argb			int2argb(int color)
{
	return ((t_argb){
		(color >> 24) & 0xFF,
		(color >> 16) & 0xFF,
		(color >> 8) & 0xFF,
		(color) & 0xFF
	});
}

int				argb(int a, int r, int g, int b)
{
	return ((a << 24) | (r << 16) | (g << 8) | (b));
}

int				argb2int(t_argb color)
{
	return ((color.a << 24) | (color.r << 16) | (color.g << 8) | (color.b));
}

int				blend_argb(int foreground, int background)
{
	t_argb fg;
	t_argb bg;
	t_argb blend;
	double ratio;

	fg = int2argb(foreground);
	bg = int2argb(background);
	if (bg.a == 255)
		return (foreground);
	if (fg.a == 255)
		return (background);
	blend.a = (bg.a == 0 ? 0 : bg.a + fg.a);
	ratio = fg.a / 255.0;
	blend.r = (fg.r * (1 - ratio)) + (bg.r * ratio);
	blend.g = (fg.g * (1 - ratio)) + (bg.g * ratio);
	blend.b = (fg.b * (1 - ratio)) + (bg.b * ratio);
	return (argb2int(blend));
}
