/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_box.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 21:52:32 by ngontjar          #+#    #+#             */
/*   Updated: 2020/10/14 00:22:37 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				ft_draw_box(t_xy corner, t_xy size, int color, t_image *image)
{
	int y;

	y = 0;
	while (y < size.y)
	{
		ft_draw_line(
			vec2(corner.x, corner.y + y),
			vec2(corner.x + size.x, corner.y + y), color, image);
		++y;
	}
	return (TRUE);
}

void			ft_draw_cbox(t_xy center, int radius, int color, t_image *image)
{
	int y;

	y = -radius;
	while (y <= radius)
	{
		ft_draw_line(
			vec2(center.x - radius, center.y + y),
			vec2(center.x + radius, center.y + y), color, image);
		++y;
	}
}
