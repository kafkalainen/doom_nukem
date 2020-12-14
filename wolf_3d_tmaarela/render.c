/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:16:09 by ngontjar          #+#    #+#             */
/*   Updated: 2020/10/14 18:34:01 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_xy			scale(t_xy a)
{
	return (vec2(a.x * MINIMAP_SIZE, a.y * MINIMAP_SIZE));
}

void			draw_grid(t_prog *p)
{
	int		i;
	t_xy	dim;

	dim = p->map.size;
	i = 0;
	while (i < dim.y)
	{
		ft_draw_line(
			vec2(0, i * MINIMAP_SIZE),
			vec2(dim.x * MINIMAP_SIZE, i * MINIMAP_SIZE), 0, &p->image);
		++i;
	}
	i = 0;
	while (i < dim.x)
	{
		ft_draw_line(
			vec2(i * MINIMAP_SIZE, 0),
			vec2(i * MINIMAP_SIZE, dim.y * MINIMAP_SIZE), 0, &p->image);
		++i;
	}
}

void			draw_top_view(t_xy size, t_xy pos, t_xy dir, t_prog *p)
{
	int x;
	int y;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if (p->map.data[y][x] == '#')
				ft_draw_box(
					vec2(x * MINIMAP_SIZE, y * MINIMAP_SIZE),
					vec2(MINIMAP_SIZE, MINIMAP_SIZE), 0x56666B, &p->image);
			++x;
		}
		++y;
	}
	pos = vec2(pos.x * MINIMAP_SIZE, pos.y * MINIMAP_SIZE);
	dir = vec2(dir.x * MINIMAP_SIZE, dir.y * MINIMAP_SIZE);
	ft_draw_cbox(pos, MINIMAP_SIZE / 2, 0x17BEBB, &p->image);
	ft_draw_line(pos, vec2_add(pos, dir), 0xA8C256, &p->image);
}

void			render(t_prog *p)
{
	ft_clear_buffer(&p->image);
	draw_background(p->me.height, &p->image);
	draw_fov(p);
	draw_grid(p);
	draw_top_view(p->map.size, p->me.pos, p->me.dir, p);
	mlx_put_image_to_window(p->mlx, p->win, p->image.ptr, 0, 0);
}

void			draw_background(double height, t_image *image)
{
	ft_draw_box(
		vec2(0, 0),
		vec2(WIN_WIDTH, WIN_HEIGHT * height), 0xabcdef, image);
	ft_draw_box(
		vec2(0, WIN_HEIGHT * height),
		vec2(WIN_WIDTH, WIN_HEIGHT - WIN_HEIGHT * height), 0x0, image);
}
