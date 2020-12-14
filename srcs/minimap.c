/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2020/12/14 13:27:48 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../doom_nukem.h"

t_xy			scale(t_xy a)
{
	return (vec2(a.x * MINIMAP_SIZE, a.y * MINIMAP_SIZE));
}

void			draw_grid(t_home *home)
{
	int		i;
	t_xy	dim;

	dim = home->map.size;
	i = 0;
	while (i < dim.y)
	{
		ft_draw_line(
			vec2(0, i * MINIMAP_SIZE),
			vec2(dim.x * MINIMAP_SIZE, i * MINIMAP_SIZE), 0xFFFFFF, home->surf);
		++i;
	}
	i = 0;
	while (i < dim.x)
	{
		ft_draw_line(
			vec2(i * MINIMAP_SIZE, 0),
			vec2(i * MINIMAP_SIZE, dim.y * MINIMAP_SIZE), 0xFFFFFF, home->surf);
		++i;
	}
}

void			draw_top_view(t_xy size, t_xy pos, t_xy dir, t_home *home)
{
	int x;
	int y;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if (home->map.data[y][x] == '#')
				draw_rect(
					vec2(x * MINIMAP_SIZE, y * MINIMAP_SIZE),
					vec2(MINIMAP_SIZE, MINIMAP_SIZE), home, 0xFF00FF);
			++x;
		}
		++y;
	}
	printf("ASD2\n");
	pos = vec2(pos.x * MINIMAP_SIZE, pos.y * MINIMAP_SIZE);
	dir = vec2(dir.x * MINIMAP_SIZE, dir.y * MINIMAP_SIZE);
	draw_rect_center(pos, vec2(5, 5), home);
	ft_draw_line(pos, vec2_add(pos, dir), 0xA8C256, home->surf);
}
