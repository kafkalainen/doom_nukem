/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/04/20 16:14:30 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int				ft_draw_line(t_xy start, t_xy end, int color, SDL_Surface *surf)
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
		if (pos.x >= 0 && pos.x < SCREEN_WIDTH && pos.y >= 0 && pos.y < SCREEN_HEIGHT)
			put_pixel(surf, pos.x, pos.y, color);
		pos.x += ratio.x * ((start.x < end.x) ? 1 : -1);
		pos.y += ratio.y * ((start.y < end.y) ? 1 : -1);
	}
	return (TRUE);
}

void	draw_rect(t_xy xy, t_xy wh, t_frame *frame, int color)
{
	float j;
	float i;

	i = xy.x;
	j = xy.y;
	while (j < wh.y + xy.y)
	{
		ft_draw_line(vec2(i, j), vec2(i + wh.x, j), color, frame->draw_surf);
		j++;
	}
}

void	draw_rect_center(t_xy xy, t_xy wh, t_frame *frame)
{
	float j;
	float i;

	i = -wh.x / 2;
	j = -wh.y / 2;
	while (j < wh.y / 2 && i < SCREEN_WIDTH && j < SCREEN_HEIGHT)
	{
			ft_draw_line(vec2(xy.x + i, xy.y + j), vec2(xy.x + fabs(i), xy.y + j), 0x00A000, frame->draw_surf);
			j++;
	}
}

void			draw_grid(t_frame *frame)
{
	int		i;
	t_xy	dim;

	dim = vec2(1, 1);//home->map.size;
	i = 0;
	while (i < dim.y)
	{
		ft_draw_line(
			vec2(0, i * MINIMAP_SIZE),
			vec2(dim.x * MINIMAP_SIZE, i * MINIMAP_SIZE), 0xFFFFFF, frame->draw_surf);
		++i;
	}
	i = 0;
	while (i < dim.x)
	{
		ft_draw_line(
			vec2(i * MINIMAP_SIZE, 0),
			vec2(i * MINIMAP_SIZE, dim.y * MINIMAP_SIZE), 0xFFFFFF, frame->draw_surf);
		++i;
	}
}
