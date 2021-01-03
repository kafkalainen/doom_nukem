/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:38:22 by tmaarela          #+#    #+#             */
/*   Updated: 2020/11/20 15:38:22 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../doom_nukem.h"

int				ft_put_pixel(double x, double y, int color, SDL_Renderer *ren)
{
	t_argb c;
	
	c = int2argb(color);
	SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
	SDL_RenderDrawPoint(ren, x, y);
}

void	put_pixel(SDL_Surface *surf, int x, int y, int color)
{
	int *pixel;

	if (x > SCREEN_WIDTH - 1 || y > SCREEN_HEIGHT - 1 || x < 0 || y < 0)
		return ;
	pixel = surf->pixels + y * surf->pitch +
		x * surf->format->BytesPerPixel;
	*pixel = color;
}

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

void	draw_grid2(int h, int v, t_home *home)
{
	int i;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		ft_draw_line((t_xy){i, 0}, (t_xy){i, SCREEN_HEIGHT}, 0xFF8000, home->surf);
		i += h;
	}
	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		ft_draw_line((t_xy){0, i}, (t_xy){SCREEN_WIDTH, i}, 0xFF8000, home->surf);
		i += v;
	}
}

void	draw_rect_center(t_xy xy, t_xy wh, t_home *home)
{
	double j;
	double i;

	i = -wh.x / 2;
	j = -wh.y / 2;
	while (j < wh.y / 2 && i < SCREEN_WIDTH && j < SCREEN_HEIGHT)
	{
			ft_draw_line(vec2(xy.x + i, xy.y + j), vec2(xy.x + fabs(i), xy.y + j), 0x00A000, home->surf);
			j++;
	}
}
