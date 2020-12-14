/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:51:28 by ngontjar          #+#    #+#             */
/*   Updated: 2020/10/14 18:33:07 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				apply_fog(int color, double distance)
{
	int		r;
	int		g;
	int		b;
	double	f;

	f = 1.0 - (1.0 / (distance + 2.0));
	r = (int)(((color >> 16) & 0xFF) / f / 3);
	g = (int)(((color >> 8) & 0xFF) / f / 3);
	b = (int)(((color >> 0) & 0xFF) / f / 3);
	return ((r << 16) | (g << 8) | b);
}

void			ft_draw_tex_col(t_tex_col *tex, double distance, t_image *image)
{
	int		texy;
	double	screeny;
	int		color;

	texy = 0;
	screeny = tex->top;
	while (screeny < tex->bot)
	{
		if (screeny <= 0 - tex->step)
		{
			screeny += tex->step;
			++texy;
			continue;
		}
		color = tex->tex->data[texy * TEX_SIZE + tex->tex_col];
		color = apply_fog(color, distance);
		ft_draw_line(
			vec2(tex->scr_col, ceil(screeny)),
			vec2(tex->scr_col, ceil(screeny + tex->step)), color, image);
		screeny += tex->step;
		++texy;
		if (screeny > WIN_HEIGHT)
			return ;
	}
}

void			ft_draw_wall(int col, t_wall wall, t_xy ray, t_prog *p)
{
	t_tex_col	tex;
	int			height;
	double		wall_x;

	height = WIN_HEIGHT / (wall.distance * vec2_dot(p->me.dir, ray));
	tex.top = (WIN_HEIGHT * p->me.height) - (height * WALL_HEIGHT);
	tex.bot = (WIN_HEIGHT * p->me.height) + (height * WALL_HEIGHT);
	tex.scr_col = col;
	wall_x = (wall.side == HORIZONTAL_WALL) ?
		p->me.pos.x + ray.x * wall.distance :
		p->me.pos.y + ray.y * wall.distance;
	wall_x -= floor(wall_x);
	tex.tex_col = (int)(wall_x * TEX_SIZE);
	tex.line_height = tex.bot - tex.top;
	tex.step = tex.line_height / (double)TEX_SIZE;
	tex.tex = &p->wall[get_wall_side(wall, p)];
	ft_draw_tex_col(&tex, wall.distance, &p->image);
}
