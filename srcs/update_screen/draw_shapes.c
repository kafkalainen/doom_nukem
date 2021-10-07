/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/10/07 11:03:14 by jnivala          ###   ########.fr       */
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
	if (!pixels)
		return (FALSE);
	delta.x /= pixels;
	delta.y /= pixels;
	pixel.x = p0.x;
	pixel.y = p0.y;
	while (pixels)
	{
		corr_pxl = (t_pxl_coords){(int)pixel.x, (int)pixel.y};
		put_pixel(buffer, corr_pxl, colour);
		pixel = vec2_add(pixel, delta);
		--pixels;
	}
	return (TRUE);
}

void	draw_rect(t_xy xy, t_xy wh, t_buffer *buffer, int color)
{
	t_pxl_coords	start;
	t_pxl_coords	end;

	start = (t_pxl_coords){xy.x, xy.y};
	end = (t_pxl_coords){start.x + wh.x, start.y + wh.y};
	while (start.y < end.y)
	{
		start.x = xy.x;
		while (start.x < end.x)
		{
			put_pixel(buffer, start, color);
			start.x++;
		}
		start.y++;
	}
}

void	draw_box(t_box box, t_buffer *buffer, Uint32 color)
{
	t_pxl_coords	start;
	t_pxl_coords	end;

	start = (t_pxl_coords){box.start.x, box.start.y};
	end = (t_pxl_coords){box.end.x, box.end.y};
	while (start.y < end.y)
	{
		start.x = box.start.x;
		while (start.x < end.x)
		{
			put_pixel(buffer, start, color);
			start.x++;
		}
		start.y++;
	}
}

t_xy	center_to_screen(t_xy loc)
{
	loc.x *= 20;
	loc.y *= 20;
	loc.x += 0.5 * SCREEN_WIDTH;
	loc.y += 0.5 * SCREEN_HEIGHT;
	return (loc);
}
