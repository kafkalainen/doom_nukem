/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/20 12:33:42 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	draw_line(t_xy p0, t_xy p1, Uint32 colour, t_buffer *buffer)
{
	t_xy			delta;
	t_xy			pixel;
	long int		pixels;
	t_pxl_coords	corr_pxl;

	delta.x = p1.x - p0.x;
	delta.y = p1.y - p0.y;
	pixels = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	delta.x /= pixels;
	delta.y /= pixels;
	pixel.x = p0.x;
	pixel.y = p0.y;
	while (pixels)
	{
		corr_pxl.x = (int)pixel.x;
		corr_pxl.y = (int)pixel.y;
		put_pixel(buffer, corr_pxl, colour);
		pixel.x += delta.x;
		pixel.y += delta.y;
		--pixels;
	}
	return (TRUE);
}

void	draw_rect(t_xy xy, t_xy wh, t_buffer *buffer, int color)
{
	float	j;
	float	i;

	i = xy.x;
	j = xy.y;
	while (j < wh.y + xy.y)
	{
		draw_line(vec2(i, j), vec2(i + wh.x, j), color, buffer);
		j++;
	}
}

void	draw_rect_center(t_xy xy, t_xy wh, t_frame *frame)
{
	float	j;
	float	i;

	i = -wh.x / 2;
	j = -wh.y / 2;
	while (j < wh.y / 2 && i < SCREEN_WIDTH && j < SCREEN_HEIGHT)
	{
		draw_line(vec2(xy.x + i, xy.y + j),
			vec2(xy.x + fabs(i), xy.y + j), 0x00A000, &frame->buffer);
		j++;
	}
}

void	draw_grid(t_frame *frame)
{
	int		i;
	t_xy	dim;

	dim = vec2(1, 1);
	i = 0;
	while (i < dim.y)
	{
		draw_line(
			vec2(0, i * MINIMAP_SIZE),
			vec2(dim.x * MINIMAP_SIZE, i * MINIMAP_SIZE), white, &frame->buffer);
		++i;
	}
	i = 0;
	while (i < dim.x)
	{
		draw_line(
			vec2(i * MINIMAP_SIZE, 0),
			vec2(i * MINIMAP_SIZE, dim.y * MINIMAP_SIZE), white, &frame->buffer);
		++i;
	}
}

t_xy	center_to_screen(t_xy loc)
{
	loc.x += 0.5 * SCREEN_WIDTH;
	loc.y += 0.5 * SCREEN_HEIGHT;
	return (loc);
}
