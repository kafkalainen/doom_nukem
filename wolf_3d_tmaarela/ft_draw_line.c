/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:25:34 by ngontjar          #+#    #+#             */
/*   Updated: 2020/10/13 23:36:54 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Requires mlx images
*/

int				ft_draw_line(t_xy start, t_xy end, int color, t_image *image)
{
	t_xy	length;
	t_xy	ratio;
	int		pixels;
	t_xy	pos;

	length = vec2(fabs(end.x - start.x), fabs(end.y - start.y));
	pixels = (length.x > length.y) ? (length.x) : (length.y);
	ratio.x = (start.y != end.y) ? (length.x / length.y) : 1;
	ratio.y = (start.x != end.x) ? (length.y / length.x) : 1;
	ratio.x = (ratio.x > ratio.y) ? 1 : (ratio.x);
	ratio.y = (ratio.y > ratio.x) ? 1 : (ratio.y);
	pos.x = start.x;
	pos.y = start.y;
	while (pixels-- > 0)
	{
		ft_put_pixel(pos.x, pos.y, color, image);
		pos.x += ratio.x * ((start.x < end.x) ? 1 : -1);
		pos.y += ratio.y * ((start.y < end.y) ? 1 : -1);
	}
	return (TRUE);
}
